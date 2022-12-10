export module NEStor.Assembly:Instructions;

import :InstructionsPrivate;
import :AddressModes;
import :Mnemonics;

import NEStor.Common;

import <concepts>;

namespace nes::assembly
{
    export using AndImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x29, .cycles = 2}, Immediate>;
    export using BrkImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::BRK, .opcode = 0x00, .cycles = 7}, Implied>;
    export using JmpAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::JMP, .opcode = 0x4C, .cycles = 3}, Absolute>;
    export using JmpIndirect = GenericInstruction<{.mnemonic = InstructionMnemonic::JMP, .opcode = 0x6C, .cycles = 5}, Indirect>;

    export using InstructionSet = GenericInstructionSet<
        AndImmediate,
        BrkImplied,
        JmpAbsolute,
        JmpIndirect
    >;

    export using InstructionVariant = GenericInstructionVariant<InstructionSet>;

} // namespace nes::assembly
