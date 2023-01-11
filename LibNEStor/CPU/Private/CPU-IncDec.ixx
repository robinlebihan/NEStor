export module NEStor.CPU:IncDec;

import :State;

import NEStor.Common;
import NEStor.Assembly;

export import <optional>;

namespace nes::cpu
{
    export enum class IncAction
    {
        Increment,
        Decrement
    };

    export template <typename T>
    struct IncDecInstructionTrait;

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::DEC> Instr>
    struct IncDecInstructionTrait<Instr>
    {
        static constexpr Byte CPUState::*Target = nullptr;
        static constexpr auto            Action = IncAction::Decrement;
    };

    export template <>
    struct IncDecInstructionTrait<assembly::DexImplied>
    {
        static constexpr auto Target = &CPUState::x;
        static constexpr auto Action = IncAction::Decrement;
    };

    export template <>
    struct IncDecInstructionTrait<assembly::DeyImplied>
    {
        static constexpr auto Target = &CPUState::y;
        static constexpr auto Action = IncAction::Decrement;
    };

    export template <assembly::concepts::InstructionWithMnemonic<assembly::InstructionMnemonic::INC> Instr>
    struct IncDecInstructionTrait<Instr>
    {
        static constexpr Byte CPUState::*Target = nullptr;
        static constexpr auto            Action = IncAction::Increment;
    };

    export template <>
    struct IncDecInstructionTrait<assembly::InxImplied>
    {
        static constexpr auto Target = &CPUState::x;
        static constexpr auto Action = IncAction::Increment;
    };

    export template <>
    struct IncDecInstructionTrait<assembly::InyImplied>
    {
        static constexpr auto Target = &CPUState::y;
        static constexpr auto Action = IncAction::Increment;
    };

    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept IncDecInstruction = requires() {
            { decay_copy(IncDecInstructionTrait<T>::Target) } -> std::same_as<Byte CPUState::*>;
            { decay_copy(IncDecInstructionTrait<T>::Action) } -> std::same_as<IncAction>;
        };
        // clang-format on

    } // namespace concepts

} // namespace nes::cpu
