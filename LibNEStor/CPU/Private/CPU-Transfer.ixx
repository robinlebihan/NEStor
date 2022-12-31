export module NEStor.CPU:Transfer;

import :State;

import NEStor.Common;
import NEStor.Assembly;

namespace nes::cpu
{
    template <typename T>
    struct TransferInstructionTrait;

    export template <>
    struct TransferInstructionTrait<assembly::TaxImplied>
    {
        static constexpr auto From = &CPUState::accumulator;
        static constexpr auto To   = &CPUState::x;
    };

    export template <>
    struct TransferInstructionTrait<assembly::TayImplied>
    {
        static constexpr auto From = &CPUState::accumulator;
        static constexpr auto To   = &CPUState::y;
    };

    export template <>
    struct TransferInstructionTrait<assembly::TsxImplied>
    {
        static constexpr auto From = &CPUState::stack_pointer;
        static constexpr auto To   = &CPUState::x;
    };

    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept TransferInstruction = requires() {
            { decay_copy(TransferInstructionTrait<T>::From) } -> std::same_as<Byte CPUState::*>;
            { decay_copy(TransferInstructionTrait<T>::To) } -> std::same_as<Byte CPUState::*>;
        };
        // clang-format on

    } // namespace concepts


} // namespace nes::cpu
