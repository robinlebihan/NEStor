import NEStor.Assembly;

#include <iostream>
#include <vector>

auto main() -> int
{
    const auto program = std::vector<nes::assembly::InstructionVariant>{
        nes::assembly::JmpAbsolute{0x1234}, nes::assembly::BccRelative{0x12}, nes::assembly::AndImmediate{0x34},
        nes::assembly::ClcImplied{}};

    std::vector<nes::Byte> encoded;
    for (const auto& instr : program)
    {
        std::ranges::copy(nes::assembly::Encode(instr), std::back_inserter(encoded));
    }

    return 0;
}