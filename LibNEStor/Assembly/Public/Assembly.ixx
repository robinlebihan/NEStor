export module NEStor.Assembly;

export import :Concepts;
export import :InstructionMetadata;
export import :AddressModes;
export import :Mnemonics;
export import :Instructions;
import :Decode;

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

} // namespace nes::assembly
