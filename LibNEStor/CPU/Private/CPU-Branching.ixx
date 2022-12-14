export module NEStor.CPU:Branching;

import :State;
import :StatusFlags;

import NEStor.Assembly;

import <concepts>;

namespace nes::cpu
{
    export template <typename T>
    struct BranchingInstructionTrait;

    export template <>
    struct BranchingInstructionTrait<assembly::BccRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return not state.status.GetFlag(StatusFlag::Carry);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BcsRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return state.status.GetFlag(StatusFlag::Carry);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BeqRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return state.status.GetFlag(StatusFlag::Zero);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BmiRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return state.status.GetFlag(StatusFlag::Negative);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BneRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return not state.status.GetFlag(StatusFlag::Zero);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BplRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return not state.status.GetFlag(StatusFlag::Negative);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BvcRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return not state.status.GetFlag(StatusFlag::Overflow);
        }
    };

    export template <>
    struct BranchingInstructionTrait<assembly::BvsRelative>
    {
        [[nodiscard]] static constexpr auto ShouldBranch(const CPUState& state) -> bool
        {
            return state.status.GetFlag(StatusFlag::Overflow);
        }
    };

    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept BranchingInstruction = requires(CPUState state) {
            { BranchingInstructionTrait<T>::ShouldBranch(state) } -> std::same_as<bool>;
        };
        // clang-format on

    } // namespace concepts

} // namespace nes::cpu