export module NEStor.Assembly:AddressModesPrivate;

import NEStor.Common;

import <type_traits>;
import <concepts>;
import <compare>;

namespace nes::assembly
{
    export struct NoOperand
    {
        constexpr auto operator<=>(const NoOperand&) const noexcept = default;
    };

    export enum class AddressModeType : Byte
    {
        Accumulator,
        Absolute,
        AbsoluteX,
        AbsoluteY,
        Immediate,
        Implied,
        Indirect,
        IndirectX,
        IndirectY,
        Relative,
        Zeropage,
        ZeropageX,
        ZeropageY
    };

    export template <AddressModeType Type, typename OperandType>
    struct [[nodiscard]] GenericAddressMode
    {
        using Operand = OperandType;

        static_assert(std::is_empty_v<Operand> or std::same_as<Operand, Word> or std::same_as<Operand, Byte>);

        static constexpr auto HasOperand = not std::is_empty_v<Operand>;
        static constexpr auto Size       = HasOperand ? sizeof(OperandType) : 0u;

        constexpr auto operator<=>(const GenericAddressMode&) const noexcept = default;

        [[msvc::no_unique_address]] Operand operand;
    };

} // namespace nes::assembly
