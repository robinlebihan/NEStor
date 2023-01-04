export module NEStor.Assembly:Instructions;

import :InstructionsPrivate;
import :AddressModes;
import :Mnemonics;
import :Concepts;

import NEStor.Common;

import <concepts>;
import <string>;

namespace nes::assembly
{
    export using AdcImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x69, .cycles = 2}, Immediate>;
    export using AdcZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x65, .cycles = 3}, Zeropage>;
    export using AdcZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x75, .cycles = 4}, ZeropageX>;
    export using AdcAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x6D, .cycles = 4}, Absolute>;
    export using AdcAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x7D, .cycles = 4}, AbsoluteX>;
    export using AdcAbsoluteY = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x79, .cycles = 4}, AbsoluteX>;
    export using AdcIndirectX = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x61, .cycles = 6}, IndirectX>;
    export using AdcIndirectY = GenericInstruction<{.mnemonic = InstructionMnemonic::ADC, .opcode = 0x71, .cycles = 5}, IndirectY>;

    export using AndImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x29, .cycles = 2}, Immediate>;
    export using AndZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x25, .cycles = 3}, Zeropage>;
    export using AndZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x35, .cycles = 4}, ZeropageX>;
    export using AndAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x2D, .cycles = 4}, Absolute>;
    export using AndAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x3D, .cycles = 4}, AbsoluteX>;
    export using AndAbsoluteY = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x39, .cycles = 4}, AbsoluteY>;
    export using AndIndirectX = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x21, .cycles = 6}, IndirectX>;
    export using AndIndirectY = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x31, .cycles = 5}, IndirectY>;

    export using AslAccumulator  = GenericInstruction<{.mnemonic = InstructionMnemonic::ASL, .opcode = 0x0A, .cycles = 2}, Accumulator>;
    export using AslZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::ASL, .opcode = 0x06, .cycles = 5}, Zeropage>;
    export using AslZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::ASL, .opcode = 0x16, .cycles = 6}, ZeropageX>;
    export using AslAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::ASL, .opcode = 0x0E, .cycles = 6}, Absolute>;
    export using AslAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::ASL, .opcode = 0x1E, .cycles = 7}, AbsoluteX>;

    export using BccRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BCC, .opcode = 0x90, .cycles = 2}, Relative>;

    export using BcsRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BCS, .opcode = 0xB0, .cycles = 2}, Relative>;

    export using BeqRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BEQ, .opcode = 0xF0, .cycles = 2}, Relative>;

    export using BitZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::BIT, .opcode = 0x24, .cycles = 3}, Zeropage>;
    export using BitAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::BIT, .opcode = 0x2C, .cycles = 4}, Absolute>;

    export using BmiRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BMI, .opcode = 0x30, .cycles = 2}, Relative>;

    export using BneRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BNE, .opcode = 0xD0, .cycles = 2}, Relative>;

    export using BplRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BPL, .opcode = 0x10, .cycles = 2}, Relative>;

    export using BrkImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::BRK, .opcode = 0x00, .cycles = 7}, Implied>;

    export using BvcRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BVC, .opcode = 0x50, .cycles = 2}, Relative>;

    export using BvsRelative = GenericInstruction<{.mnemonic = InstructionMnemonic::BVS, .opcode = 0x70, .cycles = 2}, Relative>;

    export using ClcImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::CLC, .opcode = 0x18, .cycles = 2}, Implied>;

    export using CldImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::CLD, .opcode = 0xD8, .cycles = 2}, Implied>;

    export using CliImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::CLI, .opcode = 0x58, .cycles = 2}, Implied>;

    export using ClvImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::CLV, .opcode = 0xB8, .cycles = 2}, Implied>;

    export using CmpImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xC9, .cycles = 2}, Immediate>;
    export using CmpZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xC5, .cycles = 3}, Zeropage>;
    export using CmpZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xD5, .cycles = 4}, ZeropageX>;
    export using CmpAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xCD, .cycles = 4}, Absolute>;
    export using CmpAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xDD, .cycles = 4}, AbsoluteX>;
    export using CmpAbsoluteY = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xD9, .cycles = 4}, AbsoluteY>;
    export using CmpIndirectX = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xC1, .cycles = 6}, IndirectX>;
    export using CmpIndirectY = GenericInstruction<{.mnemonic = InstructionMnemonic::CMP, .opcode = 0xD1, .cycles = 5}, IndirectY>;

    export using CpxImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::CPX, .opcode = 0xE0, .cycles = 2}, Immediate>;
    export using CpxZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::CPX, .opcode = 0xE4, .cycles = 3}, Zeropage>;
    export using CpxAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::CPX, .opcode = 0xEC, .cycles = 4}, Absolute>;

    export using CpyImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::CPY, .opcode = 0xC0, .cycles = 2}, Immediate>;
    export using CpyZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::CPY, .opcode = 0xC4, .cycles = 3}, Zeropage>;
    export using CpyAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::CPY, .opcode = 0xCC, .cycles = 4}, Absolute>;

    export using DexImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::DEX, .opcode = 0xCA, .cycles = 2}, Implied>;

    export using DeyImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::DEY, .opcode = 0x88, .cycles = 2}, Implied>;

    export using JmpAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::JMP, .opcode = 0x4C, .cycles = 3}, Absolute>;
    export using JmpIndirect = GenericInstruction<{.mnemonic = InstructionMnemonic::JMP, .opcode = 0x6C, .cycles = 5}, Indirect>;

    export using LdaImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xA9, .cycles = 2}, Immediate>;
    export using LdaZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xA5, .cycles = 3}, Zeropage>;
    export using LdaZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xB5, .cycles = 4}, ZeropageX>;
    export using LdaAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xAD, .cycles = 4}, Absolute>;
    export using LdaAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xBD, .cycles = 4}, AbsoluteX>;
    export using LdaAbsoluteY = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xB9, .cycles = 4}, AbsoluteY>;
    export using LdaIndirectX = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xA1, .cycles = 6}, IndirectX>;
    export using LdaIndirectY = GenericInstruction<{.mnemonic = InstructionMnemonic::LDA, .opcode = 0xB1, .cycles = 5}, IndirectY>;

    export using LdxImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::LDX, .opcode = 0xA2, .cycles = 2}, Immediate>;
    export using LdxZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::LDX, .opcode = 0xA6, .cycles = 3}, Zeropage>;
    export using LdxZeropageY = GenericInstruction<{.mnemonic = InstructionMnemonic::LDX, .opcode = 0xB6, .cycles = 4}, ZeropageY>;
    export using LdxAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::LDX, .opcode = 0xAE, .cycles = 4}, Absolute>;
    export using LdxAbsoluteY = GenericInstruction<{.mnemonic = InstructionMnemonic::LDX, .opcode = 0xBE, .cycles = 4}, AbsoluteY>;

    export using LdyImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::LDY, .opcode = 0xA0, .cycles = 2}, Immediate>;
    export using LdyZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::LDY, .opcode = 0xA4, .cycles = 3}, Zeropage>;
    export using LdyZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::LDY, .opcode = 0xB4, .cycles = 4}, ZeropageX>;
    export using LdyAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::LDY, .opcode = 0xAC, .cycles = 4}, Absolute>;
    export using LdyAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::LDY, .opcode = 0xBC, .cycles = 4}, AbsoluteX>;

    export using StaZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x85, .cycles = 3}, Zeropage>;
    export using StaZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x95, .cycles = 4}, ZeropageX>;
    export using StaAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x8D, .cycles = 4}, Absolute>;
    export using StaAbsoluteX = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x9D, .cycles = 5}, AbsoluteX>;
    export using StaAbsoluteY = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x99, .cycles = 5}, AbsoluteY>;
    export using StaIndirectX = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x81, .cycles = 6}, IndirectX>;
    export using StaIndirectY = GenericInstruction<{.mnemonic = InstructionMnemonic::STA, .opcode = 0x91, .cycles = 6}, IndirectY>;

    export using StxZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::STX, .opcode = 0x86, .cycles = 3}, Zeropage>;
    export using StxZeropageY = GenericInstruction<{.mnemonic = InstructionMnemonic::STX, .opcode = 0x96, .cycles = 4}, ZeropageY>;
    export using StxAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::STX, .opcode = 0x8E, .cycles = 4}, Absolute>;

    export using StyZeropage = GenericInstruction<{.mnemonic = InstructionMnemonic::STY, .opcode = 0x84, .cycles = 3}, Zeropage>;
    export using StyZeropageX = GenericInstruction<{.mnemonic = InstructionMnemonic::STY, .opcode = 0x94, .cycles = 4}, ZeropageX>;
    export using StyAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::STY, .opcode = 0x8C, .cycles = 4}, Absolute>;

    export using NopImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::NOP, .opcode = 0xEA, .cycles = 2}, Implied>;

    export using PhaImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::PHA, .opcode = 0x48, .cycles = 3}, Implied>;

    export using PhpImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::PHP, .opcode = 0x08, .cycles = 3}, Implied>;

    export using PlaImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::PLA, .opcode = 0x68, .cycles = 4}, Implied>;

    export using PlpImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::PLP, .opcode = 0x28, .cycles = 4}, Implied>;

    export using TaxImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::TAX, .opcode = 0xAA, .cycles = 2}, Implied>;

    export using TayImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::TAY, .opcode = 0xA8, .cycles = 2}, Implied>;

    export using TsxImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::TSX, .opcode = 0xBA, .cycles = 2}, Implied>;

    export using InstructionSet = GenericInstructionSet<
        // ADC
        AdcImmediate,
        AdcZeropage,
        AdcZeropageX,
        AdcAbsolute,
        AdcAbsoluteX,
        AdcAbsoluteY,
        AdcIndirectX,
        AdcIndirectY,

        // AND
        AndImmediate,
        AndZeropage,
        AndZeropageX,
        AndAbsolute,
        AndAbsoluteX,
        AndAbsoluteY,
        AndIndirectX,
        AndIndirectY,

        // ASL
        AslAccumulator,
        AslZeropage,
        AslZeropageX,
        AslAbsolute,
        AslAbsoluteX,

        // BCC
        BccRelative,

        // BCS
        BcsRelative,

        // BEQ
        BeqRelative,

        // BIT
        BitZeropage,
        BitAbsolute,

        // BMI
        BmiRelative,

        // BNE
        BneRelative,

        // BPL
        BplRelative,

        // BRK
        BrkImplied,

        // BVC
        BvcRelative,

        // BVS
        BvsRelative,

        // CLC
        ClcImplied,

        // CLD
        CldImplied,

        // CLI
        CliImplied,

        // CLV
        ClvImplied,

        // CMP
        CmpImmediate,
        CmpZeropage,
        CmpZeropageX,
        CmpAbsolute,
        CmpAbsoluteX,
        CmpAbsoluteY,
        CmpIndirectX,
        CmpIndirectY,

        // CPX
        CpxImmediate,
        CpxZeropage,
        CpxAbsolute,

        // CPY
        CpyImmediate,
        CpyZeropage,
        CpyAbsolute,

        // DEX
        DexImplied,

        // JMP
        JmpAbsolute,
        JmpIndirect,

        // LDA
        LdaImmediate,
        LdaZeropage,
        LdaZeropageX,
        LdaAbsolute,
        LdaAbsoluteX,
        LdaAbsoluteY,
        LdaIndirectX,
        LdaIndirectY,

        // LDX
        LdxImmediate,
        LdxZeropage,
        LdxZeropageY,
        LdxAbsolute,
        LdxAbsoluteY,

        // LDY
        LdyImmediate,
        LdyZeropage,
        LdyZeropageX,
        LdyAbsolute,
        LdyAbsoluteX,

        // NOP
        NopImplied,

        // PHA
        PhaImplied,

        // PHP
        PhpImplied,

        // PLA
        PlaImplied,

        // PLP
        PlpImplied,

        // STA
        StaZeropage,
        StaZeropageX,
        StaAbsolute,
        StaAbsoluteX,
        StaAbsoluteY,
        StaIndirectX,
        StaIndirectY,

        // STX
        StxZeropage,
        StxZeropageY,
        StxAbsolute,

        // STY
        StyZeropage,
        StyZeropageX,
        StyAbsolute,

        // TAX
        TaxImplied,

        // TAY
        TayImplied,

        // TSX
        TsxImplied
    >;

    export using InstructionVariant = GenericInstructionVariant<InstructionSet>;

} // namespace nes::assembly

namespace std
{
    export template <nes::assembly::concepts::Instruction Instr>
    auto to_string(const Instr& instruction) -> string
    {
        return std::format("{} {}", Instr::Metadata.mnemonic, to_string(instruction.GetAddressMode()));
    }

    export template <nes::assembly::concepts::Instruction Instr, typename CharT>
    struct formatter<Instr, CharT> : formatter<string, CharT>
    {
        template <typename FormatContext>
        auto format(const Instr& instr, FormatContext& ctx) const
        {
            return formatter<string, CharT>::format(to_string(instr), ctx);
        }
    };

} // namespace std
