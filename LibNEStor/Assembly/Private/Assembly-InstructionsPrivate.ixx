export module NEStor.Assembly:InstructionsPrivate;

import :Mnemonics;
import :Concepts;

import NEStor.Common;

import <variant>;

namespace nes::assembly
{
    export template <InstructionMetadata M, concepts::AddressMode AddressMode>
    class [[nodiscard]] GenericInstruction
    {
    public:
        static constexpr auto Metadata = M;

        using AddressModeType = AddressMode;

        constexpr GenericInstruction()
            requires not AddressMode::HasOperand = default;

        constexpr explicit GenericInstruction(AddressMode address_mode)
            : m_address_mode{address_mode}
        {}

        constexpr explicit GenericInstruction(AddressMode::Operand operand) requires AddressMode::HasOperand
            : m_address_mode{operand}
        {}

        constexpr auto operator<=>(const GenericInstruction&) const noexcept = default;

        [[nodiscard]] constexpr auto GetOperand() const noexcept { return m_address_mode.operand; }
        [[nodiscard]] constexpr auto GetAddressMode() const noexcept -> const auto& { return m_address_mode; }

    private:
        AddressModeType m_address_mode;
    };

    export template <typename... T>
    struct GenericInstructionSet;

    export template <typename T>
    struct GenericInstructionVariant;

    export template <concepts::Instruction... T>
    struct GenericInstructionVariant<GenericInstructionSet<T...>> : std::variant<std::monostate, T...>
    {
        using UnknownInstruction = std::monostate;

        using Base = std::variant<UnknownInstruction, T...>;
        using Base::Base;
        using Base::operator=;

        [[nodiscard]] constexpr auto GetSize() const noexcept
        {
            const auto get_operand_size = []<typename Instr>(const Instr & instr) -> std::size_t {
                if constexpr (std::same_as<UnknownInstruction, Instr>)
                {
                    return 0u;
                }
                else
                {
                    return Instr::AddressModeType::Size;
                }
            };

            return sizeof(Byte) + std::visit(get_operand_size, *this);
        }

        [[nodiscard]] constexpr auto IsValid() const noexcept
        {
            return not std::holds_alternative<UnknownInstruction>(*this);
        }
    };

} // namespace nes::assembly