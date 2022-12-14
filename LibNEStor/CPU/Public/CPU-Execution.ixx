export module NEStor.CPU:Execution;

import :State;
import :ExecutionVisitor;

import NEStor.Common;
import NEStor.Assembly;
import NEStor.Bus;

namespace nes::cpu
{
    export template <bus::concepts::Bus Bus>
    constexpr auto Execute(const assembly::InstructionVariant& instruction, CPUState & cpu_state, Bus& bus) -> Byte
    {
        return std::visit(InstructionExecutionVisitor{cpu_state, bus}, instruction);
    }

} // namespace nes::cpu