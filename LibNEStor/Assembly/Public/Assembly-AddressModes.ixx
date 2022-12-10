export module NEStor.Assembly:AddressModes;

import :AddressModesPrivate;

import NEStor.Common;

import <concepts>;
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