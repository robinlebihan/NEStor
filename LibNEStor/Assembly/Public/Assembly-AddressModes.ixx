export module NEStor.Assembly:AddressModes;

import NEStor.Common;

import <concepts>;
import <type_traits>;
export import <variant>;

namespace nes::assembly
{
    export struct NoOperand
    {
        constexpr auto operator<=>(const NoOperand&) const noexcept = default;
    };

    export enum class AddressModeType
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

    template <AddressModeType Type, typename OperandType>
    struct [[nodiscard]] GenericAddressMode
    {
        using Operand = OperandType;

        static_assert(std::is_empty_v<Operand> or std::same_as<Operand, Word> or std::same_as<Operand, Byte>);

        static constexpr auto HasOperand = not std::is_empty_v<Operand>;
        static constexpr auto Size       = HasOperand ? sizeof(OperandType) : 0u;

        constexpr auto operator<=>(const GenericAddressMode&) const noexcept = default;

        Operand operand;
    };

    export using ZeropageY = GenericAddressMode<AddressModeType::ZeropageY, Byte>;
    export using ZeropageX = GenericAddressMode<AddressModeType::ZeropageX, Byte>;
    export using Zeropage = GenericAddressMode<AddressModeType::Zeropage, Byte>;
    export using Relative = GenericAddressMode<AddressModeType::Relative, Byte>;
    export using IndirectY = GenericAddressMode<AddressModeType::IndirectY, Byte>;
    export using IndirectX = GenericAddressMode<AddressModeType::IndirectX, Byte>;
    export using Indirect = GenericAddressMode<AddressModeType::Indirect, Address>;
    export using Implied = GenericAddressMode<AddressModeType::Implied, NoOperand>;
    export using Immediate = GenericAddressMode<AddressModeType::Immediate, Byte>;
    export using AbsoluteY = GenericAddressMode<AddressModeType::AbsoluteY, Address>;
    export using AbsoluteX = GenericAddressMode<AddressModeType::AbsoluteX, Address>;
    export using Absolute = GenericAddressMode<AddressModeType::Absolute, Address>;
    export using Accumulator = GenericAddressMode<AddressModeType::Accumulator, NoOperand>;

    export using AddressMode = std::variant<
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
    >;

} // namespace nes::assembly