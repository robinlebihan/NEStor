export module NEStor.CPU:Impl;

import :State;
import :Execution;

import NEStor.Common;
import NEStor.Bus;
import NEStor.Assembly;

namespace nes::cpu
{
    export template <bus::concepts::ExtendedBus Bus>
    class CPU
    {
    public:
        void Update(Bus& bus)
        {
            if (m_state.instruction_remaining_cycles == 0u)
            {
                const Byte opcode  = bus.ReadByte(m_state.program_counter);
                const Word operand = bus.ReadWord(m_state.program_counter + 1);

                const auto instruction = assembly::Decode(opcode, operand);
                m_state.program_counter += static_cast<Address>(instruction.GetSize());

                const auto cycles_to_perform         = Execute(instruction, m_state, bus);
                m_state.instruction_remaining_cycles = cycles_to_perform;
            }

            m_state.instruction_remaining_cycles--;
            m_state.total_cycles++;
        }

        auto GetState() const noexcept { return m_state; }

    private:
        CPUState m_state;
    };

} // namespace nes::cpu
