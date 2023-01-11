export module NEStor.CPU:Store;

import :State;

import NEStor.Common;
import NEStor.Assembly;

namespace nes::cpu
{
    template <typename T>
    struct StoreInstructionTrait;

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::STA> Instr>
    struct StoreInstructionTrait<Instr>
    {
        static constexpr auto Source = &CPUState::accumulator;
    };

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::STX> Instr>
    struct StoreInstructionTrait<Instr>
    {
        static constexpr auto Source = &CPUState::x;
    };

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::STY> Instr>
    struct StoreInstructionTrait<Instr>
    {
        static constexpr auto Source = &CPUState::y;
    };

    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept StoreInstruction = requires() {
            { decay_copy(StoreInstructionTrait<T>::Source) } -> std::same_as<Byte CPUState::*>;
        };
        // clang-format on

    } // namespace concepts


} // namespace nes::cpu
