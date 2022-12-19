export module NEStor.Assembly:Mnemonics;

import NEStor.Common;

import <format>;
import <string>;
import <utility>;

namespace nes::assembly
{
    export enum class InstructionMnemonic : Byte
    {
        ADC,
        AND,
        ASL,
        BCC,
        BCS,
        BEQ,
        BIT,
        BMI,
        BNE,
        BPL,
        BRK,
        BVC,
        BVS,
        CLC,
        CLD,
        CLI,
        CLV,
        CMP,
        CPX,
        CPY,
        DEC,
        DEX,
        DEY,
        EOR,
        INC,
        INX,
        INY,
        JMP,
        JSR,
        LDA,
        LDX,
        LDY,
        LSR,
        NOP,
        ORA,
        PHA,
        PHP,
        PLA,
        PLP,
        ROL,
        ROR,
        RTI,
        RTS,
        SBC,
        SEC,
        SED,
        SEI,
        STA,
        STX,
        STY,
        TAX,
        TAY,
        TSX,
        TXA,
        TXS,
        TYA
    };

} // namespace nes::assembly

namespace std
{
    export auto to_string(nes::assembly::InstructionMnemonic mnemonic) -> string
    {
        using enum nes::assembly::InstructionMnemonic;

        switch (mnemonic)
        {
        case ADC:
            return "ADC";
        case AND:
            return "AND";
        case ASL:
            return "ASL";
        case BCC:
            return "BCC";
        case BCS:
            return "BCS";
        case BEQ:
            return "BEQ";
        case BIT:
            return "BIT";
        case BMI:
            return "BMI";
        case BNE:
            return "BNE";
        case BPL:
            return "BPL";
        case BRK:
            return "BRK";
        case BVC:
            return "BVC";
        case CLC:
            return "CLC";
        case CLD:
            return "CLD";
        case CLI:
            return "CLI";
        case CLV:
            return "CLV";
        case CMP:
            return "CMP";
        case CPX:
            return "CPX";
        case CPY:
            return "CPY";
        case DEC:
            return "DEC";
        case DEX:
            return "DEX";
        case DEY:
            return "DEY";
        case EOR:
            return "EOR";
        case INC:
            return "INC";
        case INX:
            return "INX";
        case INY:
            return "INY";
        case JMP:
            return "JMP";
        case JSR:
            return "JSR";
        case LDA:
            return "LDA";
        case LDX:
            return "LDX";
        case LDY:
            return "LDY";
        case LSR:
            return "LSR";
        case NOP:
            return "NOP";
        case ORA:
            return "ORA";
        case PHA:
            return "PHA";
        case PHP:
            return "PHP";
        case PLA:
            return "PLA";
        case PLP:
            return "PLP";
        case ROL:
            return "ROL";
        case ROR:
            return "ROR";
        case RTI:
            return "RTI";
        case RTS:
            return "RTS";
        case SBC:
            return "SBC";
        case SEC:
            return "SEC";
        case SED:
            return "SED";
        case SEI:
            return "SEI";
        case STA:
            return "STA";
        case STX:
            return "STX";
        case STY:
            return "STY";
        case TAX:
            return "TAX";
        case TAY:
            return "TAY";
        case TSX:
            return "TSX";
        case TXA:
            return "TXA";
        case TXS:
            return "TXS";
        case TYA:
            return "TYA";
        default:
            return "XXX";
        }
    }

    export template <typename CharT>
    struct formatter<nes::assembly::InstructionMnemonic, CharT> : formatter<string, CharT>
    {
        template <typename FormatContext>
        auto format(nes::assembly::InstructionMnemonic value, FormatContext& ctx) const
        {
            return formatter<string, CharT>::format(to_string(value), ctx);
        }
    };

} // namespace std