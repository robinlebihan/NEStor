export module NEStor.Assembly:Decode;

import :Concepts;
import :AddressModes;
import :Instructions;

import NEStor.Common;

import <algorithm>;
import <optional>;
import <array>;

namespace nes::assembly
{
    namespace
    {
        template <concepts::Instruction... T>
        [[nodiscard]] consteval auto AreInstructionOpcodesUnique()
        {
            std::array<Byte, sizeof...(T)> opcodes{T::Metadata.opcode...};
            std::ranges::sort(opcodes);

            const auto duplicates = std::ranges::unique(opcodes);
            return std::ranges::size(duplicates) == 0u;
        }

    } // namespace

    template <typename T>
    struct InstructionMatcher;

    export template <typename... T>
    struct InstructionMatcher<GenericInstructionVariant<GenericInstructionSet<T...>>>
    {
        static_assert(AreInstructionOpcodesUnique<T...>(), "Some instructions have identical opcodes");

        using InstructionType = GenericInstructionVariant<GenericInstructionSet<T...>>;

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
                const Byte actual_operand = operand & 0x00FFu;
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
            return instruction.value_or(typename InstructionType::UnknownInstruction{});
        }
    };

} // namespace nes::assembly
