export module NEStor.CPU:ExecutionVisitor;

import :State;
import :Branching;
import :EffectiveAddress;

import NEStor.Common;
import NEStor.Assembly;
import NEStor.Bus;

import <concepts>;

namespace nes::cpu
{
    constexpr auto PageBoundaryCrossingOverhead(bool crossed_page_boundary)
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

        auto FetchByte(const assembly::Accumulator& address_mode) -> FetchedByte
        {
            return {.data = m_cpu_state.accumulator, .crossed_page_boundary = false};
        }

        auto FetchByte(const assembly::Immediate& address_mode) -> FetchedByte
        {
            return {.data = address_mode.operand, .crossed_page_boundary = false};
        }

        template <assembly::concepts::AddressMode AddressMode>
        auto FetchByte(const AddressMode& address_mode) -> FetchedByte
            requires std::same_as<AddressMode, assembly::Zeropage>
                or std::same_as<AddressMode, assembly::ZeropageX>
                or std::same_as<AddressMode, assembly::ZeropageY>
                or std::same_as<AddressMode, assembly::Absolute>
                or std::same_as<AddressMode, assembly::AbsoluteX>
                or std::same_as<AddressMode, assembly::AbsoluteY>
                or std::same_as<AddressMode, assembly::Indirect>
                or std::same_as<AddressMode, assembly::IndirectX>
                or std::same_as<AddressMode, assembly::IndirectY>
        {
            const auto [address, page_boundary_crossing] = ComputeEffectiveAddress(address_mode, m_bus, m_cpu_state);
            return {m_bus.ReadByte(address), page_boundary_crossing};
        }

        auto WriteByte(const assembly::Accumulator& address_mode, Byte data) -> bool
        {
            m_cpu_state.accumulator = data;
            return false;
        }

        template <assembly::concepts::AddressMode AddressMode>
        auto WriteByte(const AddressMode& address_mode, Byte data) -> bool
            requires std::same_as<AddressMode, assembly::Zeropage>
                or std::same_as<AddressMode, assembly::ZeropageX>
                or std::same_as<AddressMode, assembly::ZeropageY>
                or std::same_as<AddressMode, assembly::Absolute>
                or std::same_as<AddressMode, assembly::AbsoluteX>
                or std::same_as<AddressMode, assembly::AbsoluteY>
                or std::same_as<AddressMode, assembly::Indirect>
                or std::same_as<AddressMode, assembly::IndirectX>
                or std::same_as<AddressMode, assembly::IndirectY>
        {
            const auto [address, page_boundary_crossing] = ComputeEffectiveAddress(address_mode, m_bus, m_cpu_state);
            m_bus.WriteByte(address, data);
            return page_boundary_crossing;
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

            const auto result = data << 1u;
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

        template <concepts::BranchingInstruction Instr>
        auto operator()(const Instr& instr) -> Byte
        {
            const auto branching_overhead =
                ExecuteBranch(instr.GetAddressMode(), BranchingInstructionTrait<Instr>::ShouldBranch(m_cpu_state));
            return assembly::BccRelative::Metadata.cycles + branching_overhead;
        }

        auto operator()(const assembly::ClcImplied& instr) -> Byte
        {
            m_cpu_state.status.SetFlag(StatusFlag::Carry, false);
            return assembly::ClcImplied::Metadata.cycles;
        }

        auto operator()(const assembly::CldImplied& instr) -> Byte
        {
            m_cpu_state.status.SetFlag(StatusFlag::Decimal, false);
            return assembly::CldImplied::Metadata.cycles;
        }

        auto operator()(const assembly::CliImplied& instr) -> Byte
        {
            m_cpu_state.status.SetFlag(StatusFlag::InterruptDisable, false);
            return assembly::CliImplied::Metadata.cycles;
        }

        auto operator()(const assembly::ClvImplied& instr) -> Byte
        {
            m_cpu_state.status.SetFlag(StatusFlag::Overflow, false);
            return assembly::ClvImplied::Metadata.cycles;
        }

        auto operator()(const auto& instr) -> Byte
        {
            return 0u;
        }

    private:
        CPUState& m_cpu_state;
        Bus&      m_bus;
    };
} // namespace nes::cpu