export module NEStor.Assembly:AddressModes;

import :AddressModesPrivate;

import NEStor.Common;

import <concepts>;
import <string>;
import <format>;
export import <variant>;

namespace nes::assembly
{
    export using Accumulator = GenericAddressMode<AddressModeType::Accumulator, NoOperand>;
    export using Absolute = GenericAddressMode<AddressModeType::Absolute, Address>;
    export using AbsoluteX = GenericAddressMode<AddressModeType::AbsoluteX, Address>;
    export using AbsoluteY = GenericAddressMode<AddressModeType::AbsoluteY, Address>;
    export using Immediate = GenericAddressMode<AddressModeType::Immediate, Byte>;
    export using Implied = GenericAddressMode<AddressModeType::Implied, NoOperand>;
    export using Indirect = GenericAddressMode<AddressModeType::Indirect, Address>;
    export using IndirectX = GenericAddressMode<AddressModeType::IndirectX, Byte>;
    export using IndirectY = GenericAddressMode<AddressModeType::IndirectY, Byte>;
    export using Relative = GenericAddressMode<AddressModeType::Relative, Byte>;
    export using Zeropage = GenericAddressMode<AddressModeType::Zeropage, Byte>;
    export using ZeropageX = GenericAddressMode<AddressModeType::ZeropageX, Byte>;
    export using ZeropageY = GenericAddressMode<AddressModeType::ZeropageY, Byte>;

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

namespace std
{
    export auto to_string(const nes::assembly::Accumulator& /*address_mode*/) -> string
    {
        return "A";
    }

    export auto to_string(const nes::assembly::Absolute& address_mode) -> string
    {
        return std::format("${:04X}", address_mode.operand);
    }

    export auto to_string(const nes::assembly::AbsoluteX& address_mode) -> string
    {
        return std::format("${:04X},X", address_mode.operand);
    }

    export auto to_string(const nes::assembly::AbsoluteY& address_mode) -> string
    {
        return std::format("${:04X},Y", address_mode.operand);
    }

    export auto to_string(const nes::assembly::Immediate& address_mode) -> string
    {
        return std::format("#${:02X}", address_mode.operand);
    }

    export auto to_string(const nes::assembly::Implied& /*address_mode*/) -> string
    {
        return "";
    }

    export auto to_string(const nes::assembly::Indirect& address_mode) -> string
    {
        return std::format("(${:04X})", address_mode.operand);
    }

    export auto to_string(const nes::assembly::IndirectX& address_mode) -> string
    {
        return std::format("(${:02X},X)", address_mode.operand);
    }

    export auto to_string(const nes::assembly::IndirectY& address_mode) -> string
    {
        return std::format("(${:02X}),Y", address_mode.operand);
    }

    export auto to_string(const nes::assembly::Relative& address_mode) -> string
    {
        return std::format("${:02X}", address_mode.operand);
    }

    export auto to_string(const nes::assembly::Zeropage& address_mode) -> string
    {
        return std::format("${:02X}", address_mode.operand);
    }

    export auto to_string(const nes::assembly::ZeropageX& address_mode) -> string
    {
        return std::format("${:02X},X", address_mode.operand);
    }

    export auto to_string(const nes::assembly::ZeropageY& address_mode) -> string
    {
        return std::format("${:02X},Y", address_mode.operand);
    }

} // namespace std
