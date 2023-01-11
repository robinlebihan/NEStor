export module NEStor.CPU:FlagInstruction;

import :StatusFlags;

import NEStor.Common;
import NEStor.Assembly;

namespace nes::cpu
{
    template <typename T>
    struct FlagInstructionTrait;

    export enum class FlagAction
    {
        Clear,
        Set
    };

    export template <>
    struct FlagInstructionTrait<assembly::ClvImplied>
    {
        static constexpr auto Action = FlagAction::Clear;
        static constexpr auto Flag   = StatusFlag::Overflow;
    };

    export template <>
    struct FlagInstructionTrait<assembly::CliImplied>
    {
        static constexpr auto Action = FlagAction::Clear;
        static constexpr auto Flag   = StatusFlag::InterruptDisable;
    };

    export template <>
    struct FlagInstructionTrait<assembly::ClcImplied>
    {
        static constexpr auto Action = FlagAction::Clear;
        static constexpr auto Flag   = StatusFlag::Carry;
    };

    export template <>
    struct FlagInstructionTrait<assembly::CldImplied>
    {
        static constexpr auto Action = FlagAction::Clear;
        static constexpr auto Flag   = StatusFlag::Decimal;
    };

    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept FlagInstruction = requires() {
            { decay_copy(FlagInstructionTrait<T>::Action) } -> std::same_as<FlagAction>;
            { decay_copy(FlagInstructionTrait<T>::Flag) } -> std::same_as<StatusFlag>;
        };
        // clang-format on

    } // namespace concepts


} // namespace nes::cpu
