export module NEStor.Assembly:InstructionMetadata;

import :Mnemonics;

import NEStor.Common;

namespace nes::assembly
{
    export struct InstructionMetadata
    {
        InstructionMnemonic mnemonic;
        Byte                opcode;
        Byte                cycles;
    };

} // namespace nes::assembly