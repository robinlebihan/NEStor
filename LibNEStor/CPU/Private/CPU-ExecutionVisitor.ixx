export module NEStor.CPU:ExecutionVisitor;

import :IncDec;
import :State;
import :Branching;
import :EffectiveAddress;
import :Transfer;
import :FlagInstruction;
import :Load;
import :Store;

import NEStor.Common;
import NEStor.Assembly;
import NEStor.Bus;

import <concepts>;

namespace nes::cpu
{
    constexpr Address StackAddress = 0x100;

    constexpr auto PageBoundaryCrossingOverhead(bool crossed_page_boundary) -> Byte
    {
        return crossed_page_boundary ? 1u : 0u;
    }

    constexpr void UpdateFlags(CPUState& state, Byte value)
    {
        state.status.SetFlag(StatusFlag::Negative, (value & 0b1000'0000) > 0u);
        state.status.SetFlag(StatusFlag::Zero, value == 0u);
    }

    constexpr auto WrappingSub(Byte lhs, Byte rhs) -> Byte
    {
        return static_cast<Byte>(static_cast<std::int8_t>(lhs - rhs));
    }

    constexpr auto WrappingAdd(Byte lhs, Byte rhs) -> Byte
    {
        return static_cast<Byte>((static_cast<Word>(lhs) + static_cast<Word>(rhs)) & 0xFF);
    }

    template <IncAction Action>
    constexpr void IncrementOrDecrement(Byte& value)
    {
        if constexpr (Action == IncAction::Increment)
        {
            value = WrappingAdd(value, 1u);
        }
        else
        {
            value = WrappingSub(value, 1u);
        }
    }

    export template <bus::concepts::Bus Bus>
    class InstructionExecutionVisitor
    {
    public:
        InstructionExecutionVisitor(CPUState& cpu_state, Bus& bus)
            : m_cpu_state{cpu_state}
            , m_bus{bus}
        {}

        struct FetchedByte
        {
            Byte data;
            bool crossed_page_boundary;
        };

        auto FetchByte(const assembly::Accumulator& /*address_mode*/) -> FetchedByte
        {
            return {.data = m_cpu_state.accumulator, .crossed_page_boundary = false};
        }

        auto FetchByte(const assembly::Immediate& address_mode) -> FetchedByte
        {
            return {.data = address_mode.operand, .crossed_page_boundary = false};
        }

        template <assembly::concepts::AddressMode AddressMode>
        auto FetchByte(const AddressMode& address_mode) -> FetchedByte
            requires concepts::MemoryAddressMode<AddressMode, Bus>
        {
            const auto [address, page_boundary_crossing] = ComputeEffectiveAddress(address_mode, m_bus, m_cpu_state);
            return {m_bus.ReadByte(address), page_boundary_crossing};
        }

        auto WriteByte(const assembly::Accumulator& /*address_mode*/, Byte data) -> bool
        {
            m_cpu_state.accumulator = data;
            return false;
        }

        template <assembly::concepts::AddressMode AddressMode>
        auto WriteByte(const AddressMode& address_mode, Byte data) -> bool
            requires concepts::MemoryAddressMode<AddressMode, Bus>
        {
            const auto [address, page_boundary_crossing] = ComputeEffectiveAddress(address_mode, m_bus, m_cpu_state);
            m_bus.WriteByte(address, data);
            return page_boundary_crossing;
        }

        void StackPush(Byte data)
        {
            m_bus.WriteByte(StackAddress + static_cast<Address>(m_cpu_state.stack_pointer), data);
            m_cpu_state.stack_pointer = WrappingSub(m_cpu_state.stack_pointer, 1);
        }

        [[nodiscard]] auto StackPull() -> Byte
        {
            m_cpu_state.stack_pointer = WrappingAdd(m_cpu_state.stack_pointer, 1);
            return m_bus.ReadByte(StackAddress + static_cast<Address>(m_cpu_state.stack_pointer));
        }

        auto ExecuteBranch(const assembly::Relative& address_mode, bool condition) -> Byte
        {
            if (condition)
            {
                const auto [new_pc, crossed_page_boundary] = ComputeEffectiveAddress(address_mode, m_bus, m_cpu_state);
                m_cpu_state.program_counter = new_pc;

                return 1u + PageBoundaryCrossingOverhead(crossed_page_boundary);
            }

            return 0u;
        }

        auto operator()(const assembly::NopImplied& /*instr*/) -> Byte
        {
            return assembly::NopImplied::Metadata.cycles;
        }

        template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::JMP> Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto [effective_address, _] = ComputeEffectiveAddress(instr.GetAddressMode(), m_bus, m_cpu_state);
            m_cpu_state.program_counter       = effective_address;

            return Instr::Metadata.cycles;
        }

        template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::AND> Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto [data, crossed_page_boundary] = FetchByte(instr.GetAddressMode());
            m_cpu_state.accumulator &= data;
            UpdateFlags(m_cpu_state, m_cpu_state.accumulator);

            return Instr::Metadata.cycles + PageBoundaryCrossingOverhead(crossed_page_boundary);
        }

        template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::CMP> Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto [data, crossed_page_boundary] = FetchByte(instr.GetAddressMode());

            const auto sub = WrappingSub(m_cpu_state.accumulator, data);
            UpdateFlags(m_cpu_state, sub);
            m_cpu_state.status.SetFlag(StatusFlag::Carry, m_cpu_state.accumulator >= data);

            return Instr::Metadata.cycles + PageBoundaryCrossingOverhead(crossed_page_boundary);
        }

        template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::ASL> Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto [data, crossed_page_boundary] = FetchByte(instr.GetAddressMode());

            const Byte result = data << 1u;
            UpdateFlags(m_cpu_state, result);
            m_cpu_state.status.SetFlag(StatusFlag::Carry, (data & 0b1000'0000) > 0u);

            WriteByte(instr.GetAddressMode(), result);
            return Instr::Metadata.cycles + PageBoundaryCrossingOverhead(crossed_page_boundary);
        }

        template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::BIT> Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto [data, _] = FetchByte(instr.GetAddressMode());

            const auto result = m_cpu_state.accumulator & data;
            m_cpu_state.status.SetFlag(StatusFlag::Overflow, (data & 0b0100'0000) > 0u);
            m_cpu_state.status.SetFlag(StatusFlag::Negative, (data & 0b1000'0000) > 0u);
            m_cpu_state.status.SetFlag(StatusFlag::Zero, result != 0u);

            return Instr::Metadata.cycles;
        }

        template <concepts::IncDecInstruction Instr>
        auto operator()([[maybe_unused]] const Instr& instr) -> Byte
        {
            if constexpr (IncDecInstructionTrait<Instr>::Target != nullptr)
            {
                auto& target = m_cpu_state.*(IncDecInstructionTrait<Instr>::Target);
                IncrementOrDecrement<IncDecInstructionTrait<Instr>::Action>(target);
                UpdateFlags(m_cpu_state, target);
            }
            else
            {
                auto [value, _] = FetchByte(instr.GetAddressMode());
                IncrementOrDecrement<IncDecInstructionTrait<Instr>::Action>(value);
                UpdateFlags(m_cpu_state, value);
                WriteByte(instr.GetAddressMode(), value);
            }

            return Instr::Metadata.cycles;
        }

        template <concepts::BranchingInstruction Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto branching_overhead =
                ExecuteBranch(instr.GetAddressMode(), BranchingInstructionTrait<Instr>::ShouldBranch(m_cpu_state));
            return Instr::Metadata.cycles + branching_overhead;
        }

        template <concepts::TransferInstruction Instr>
        auto operator()(const Instr& /*instr*/) -> Byte
        {
            const auto from = m_cpu_state.*(TransferInstructionTrait<Instr>::From);
            auto&      to   = m_cpu_state.*(TransferInstructionTrait<Instr>::To);

            to = from;

            UpdateFlags(m_cpu_state, to);
            return Instr::Metadata.cycles;
        }

        template <concepts::FlagInstruction Instr>
        auto operator()(const Instr& /*instr*/) -> Byte
        {
            constexpr auto new_flag_value = FlagInstructionTrait<Instr>::Action == FlagAction::Set;
            m_cpu_state.status.SetFlag(FlagInstructionTrait<Instr>::Flag, new_flag_value);
            return Instr::Metadata.cycles;
        }

        template <concepts::LoadInstruction Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto [data, crossed_page_boundary] = FetchByte(instr.GetAddressMode());

            auto& target = m_cpu_state.*(LoadInstructionTrait<Instr>::Target);
            target       = data;

            UpdateFlags(m_cpu_state, target);
            return Instr::Metadata.cycles + PageBoundaryCrossingOverhead(crossed_page_boundary);
        }

        template <concepts::StoreInstruction Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto source                = m_cpu_state.*(StoreInstructionTrait<Instr>::Source);
            const auto crossed_page_boundary = WriteByte(instr.GetAddressMode(), source);
            return Instr::Metadata.cycles + PageBoundaryCrossingOverhead(crossed_page_boundary);
        }

        auto operator()(const assembly::DeyImplied& /*instr*/) -> Byte
        {
            m_cpu_state.y = WrappingSub(m_cpu_state.y, 1);
            UpdateFlags(m_cpu_state, m_cpu_state.y);

            return assembly::DeyImplied::Metadata.cycles;
        }

        auto operator()(const assembly::PhaImplied& /*instr*/) -> Byte
        {
            StackPush(m_cpu_state.accumulator);
            return assembly::PhaImplied::Metadata.cycles;
        }

        auto operator()(const assembly::PhpImplied& /*instr*/) -> Byte
        {
            StackPush(m_cpu_state.status.GetValue());
            return assembly::PhpImplied::Metadata.cycles;
        }

        auto operator()(const assembly::PlaImplied& /*instr*/) -> Byte
        {
            m_cpu_state.accumulator = StackPull();
            UpdateFlags(m_cpu_state, m_cpu_state.accumulator);
            return assembly::PlaImplied::Metadata.cycles;
        }

        auto operator()(const assembly::PlpImplied& /*instr*/) -> Byte
        {
            m_cpu_state.status = StatusRegister{StackPull()};
            return assembly::PlpImplied::Metadata.cycles;
        }

        auto operator()(const auto& /*instr*/) -> Byte
        {
            return 0u;
        }

    private:
        CPUState& m_cpu_state;
        Bus&      m_bus;
    };
} // namespace nes::cpu