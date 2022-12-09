export module NEStor.Assembly:Decode;

import :AddressModes;
import :Instructions;

import NEStor.Common;

import <optional>;

namespace nes::assembly
{
    export [[nodiscard]] constexpr auto Decode(Byte opcode, Word operand) -> Instruction;

    namespace
    {
        template <typename T>
        struct InstructionMatcher;

        template <typename... T>
        struct InstructionMatcher<InstructionVariant<GenericInstructionSet<T...>>>
        {
            using InstructionType = InstructionVariant<GenericInstructionSet<T...>>;

            template <typename Instr>
            static constexpr void MatchSingleInstruction(Byte opcode, [[maybe_unused]] Word operand, std::optional<InstructionType>& out)
            {
                if (opcode != Instr::Metadata.opcode or out.has_value())
                {
                    return;
                }

                using OperandType = Instr::AddressModeType::Operand;
                if constexpr (std::same_as<OperandType, NoOperand>)
                {
                    out = Instr{};
                }
                else if constexpr (std::same_as<OperandType, Byte>)
                {
                    const Byte actual_operand = (operand & 0xFF00u) >> 8u;
                    out = Instr{actual_operand};
                }
                else
                {
                    out = Instr{operand};
                }
            }

            static constexpr auto Match(Byte opcode, Word operand)
            {
                std::optional<InstructionType> instruction;
                (..., MatchSingleInstruction<T>(opcode, operand, instruction));
                return instruction.value_or(UnknownInstruction{});
            }
        };

    } // namespace

    constexpr auto Decode(Byte opcode, Word operand) -> Instruction
    {
        return InstructionMatcher<Instruction>::Match(opcode, operand);
    }

} // namespace nes::assembly
