export module NEStor.Assembly:Instructions;

import :AddressModes;

import NEStor.Common;

import <variant>;

namespace nes::assembly
{
    export enum class InstructionMnemonic
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

    struct InstructionMetadata
    {
        InstructionMnemonic mnemonic;
        Byte                opcode;
        Word                cycles;
    };

    export template <InstructionMetadata M, typename AddressMode>
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

    export using AndImmediate = GenericInstruction<{.mnemonic = InstructionMnemonic::AND, .opcode = 0x29, .cycles = 2}, Immediate>;
    export using BrkImplied = GenericInstruction<{.mnemonic = InstructionMnemonic::BRK, .opcode = 0x00, .cycles = 7}, Implied>;
    export using JmpAbsolute = GenericInstruction<{.mnemonic = InstructionMnemonic::JMP, .opcode = 0x4C, .cycles = 3}, Absolute>;
    export using JmpIndirect = GenericInstruction<{.mnemonic = InstructionMnemonic::JMP, .opcode = 0x6C, .cycles = 5}, Indirect>;
    export using UnknownInstruction = std::monostate;

    export template <typename... T>
    struct GenericInstructionSet;

    export using InstructionSet = GenericInstructionSet<
        AndImmediate,
        BrkImplied,
        JmpAbsolute,
        JmpIndirect
    >;

    export template <typename T>
    struct InstructionVariant;

    export template <typename... T>
    struct InstructionVariant<GenericInstructionSet<T...>> : std::variant<UnknownInstruction, T...>
    {
        using Base = std::variant<UnknownInstruction, T...>;
        using Base::Base;
        using Base::operator=;

        [[nodiscard]] constexpr auto IsValid() const noexcept
        {
            return not std::holds_alternative<UnknownInstruction>(*this);
        }
    };

    export using Instruction = InstructionVariant<InstructionSet>;

} // namespace nes::assembly
