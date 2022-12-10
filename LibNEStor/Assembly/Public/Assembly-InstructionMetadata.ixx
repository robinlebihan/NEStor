export module NEStor.Assembly:InstructionMetadata;

import :Mnemonics;

import NEStor.Common;

namespace nes::assembly
{
    export struct InstructionMetadata
    {
        InstructionMnemonic mnemonic;
        Byte                opcode;
        Word                cycles;
    };

} // namespace nes::assembly