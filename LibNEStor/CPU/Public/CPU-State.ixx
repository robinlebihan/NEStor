export module NEStor.CPU:State;

import :StatusFlags;

import NEStor.Common;

namespace nes::cpu
{
    export struct CPUState
    {
        Byte stack_pointer = 0u;
        Byte accumulator   = 0u;
        Byte x             = 0u;
        Byte y             = 0u;

        Address program_counter = 0u;

        StatusRegister status;

        Byte          instruction_remaining_cycles = 0u;
        std::uint64_t total_cycles                 = 0u;

        friend [[nodiscard]] constexpr auto operator==(const CPUState& lhs, const CPUState& rhs)
        {
            return lhs.status == rhs.status
                and lhs.program_counter == rhs.program_counter
                and lhs.y == rhs.y
                and lhs.x == rhs.x
                and lhs.accumulator == rhs.accumulator
                and lhs.stack_pointer == rhs.stack_pointer;
        }
    };

} // namespace nes::cpu
