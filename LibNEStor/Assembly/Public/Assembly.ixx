export module NEStor.Assembly;

export import :Concepts;
export import :InstructionMetadata;
export import :AddressModes;
export import :Mnemonics;
export import :Instructions;
import :Decode;

import <vector>;
import <concepts>;

namespace nes::assembly
{
    /*
    * Returns a variant representing the instruction decoded from opcode and operand.
    * The operand should be in big-endian.
    */
    export [[nodiscard]] constexpr auto Decode(Byte opcode, Word operand) -> InstructionVariant
    {
        return InstructionMatcher<InstructionVariant>::Match(opcode, operand);
    }

    export template <concepts::Instruction Instr>
    [[nodiscard]] auto Encode(const Instr& instr) -> std::vector<Byte>
    {
        std::vector<Byte> result;
        result.push_back(Instr::Metadata.opcode);

        if constexpr (std::same_as<typename Instr::AddressModeType::Operand, Word>)
        {
            const Word operand = instr.GetOperand();
            result.push_back(operand & 0x00FFu);
            result.push_back((operand & 0xFF00u) >> 8u);
        }
        else if constexpr (std::same_as<typename Instr::AddressModeType::Operand, Byte>)
        {
            result.push_back(instr.GetOperand());
        }

        return result;
    }

    export [[nodiscard]] auto Encode(const InstructionVariant& instruction) -> std::vector<Byte>
    {
        return std::visit([](const auto& instr) { return Encode(instr); }, instruction);
    }

} // namespace nes::assembly
