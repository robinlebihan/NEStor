export module NEStor.CPU:Load;

import :State;

import NEStor.Common;
import NEStor.Assembly;

namespace nes::cpu
{
    template <typename T>
    struct LoadInstructionTrait;

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::LDA> Instr>
    struct LoadInstructionTrait<Instr>
    {
        static constexpr auto Target = &CPUState::accumulator;
    };

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::LDX> Instr>
    struct LoadInstructionTrait<Instr>
    {
        static constexpr auto Target = &CPUState::x;
    };

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::LDY> Instr>
    struct LoadInstructionTrait<Instr>
    {
        static constexpr auto Target = &CPUState::y;
    };

    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept LoadInstruction = requires() {
            { decay_copy(LoadInstructionTrait<T>::Target) } -> std::same_as<Byte CPUState::*>;
        };
        // clang-format on

    } // namespace concepts


} // namespace nes::cpu
