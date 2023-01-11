export module NEStor.Assembly:Concepts;

import :InstructionMetadata;
import :Mnemonics;

import NEStor.Common;

import <concepts>;
import <variant>;

namespace nes::assembly::concepts
{
    // clang-format off
    export template <typename T>
    concept AddressMode = std::regular<T> and requires(const T address_mode) {
        typename T::Operand;

        requires std::is_empty_v<typename T::Operand>
            or std::same_as<Byte, typename T::Operand>
            or std::same_as<Word, typename T::Operand>;

        { decay_copy(address_mode.operand) } -> std::same_as<typename T::Operand>;
        { decay_copy(T::HasOperand) }        -> std::same_as<bool>;
        { decay_copy(T::Size) }              -> std::same_as<std::size_t>;
    };

    export template <typename T>
    concept Instruction = requires(const T instruction) {
        requires std::equality_comparable<T> and std::copyable<T>;

        typename T::AddressModeType;
        requires AddressMode<typename T::AddressModeType>;
        { decay_copy(instruction.GetAddressMode()) } -> std::same_as<typename T::AddressModeType>;
        { decay_copy(instruction.GetOperand()) } -> std::same_as<typename T::AddressModeType::Operand>;

        { decay_copy(T::Metadata) } -> std::same_as<InstructionMetadata>;
    };

    export template <typename T>
    concept InstructionVariant = requires(const T instruction_variant) {
        requires std::regular<T>;

        { instruction_variant.IsValid() } -> std::same_as<bool>;
        { instruction_variant.GetSize() } -> std::same_as<std::size_t>;

        std::visit([](const auto&) {}, instruction_variant);
        typename T::UnknownInstruction;
    };

    export template <typename T, InstructionMnemonic Mnem>
    concept InstructionWithMnemonic = Instruction<T> and Mnem == T::Metadata.mnemonic;
    // clang-format on

} // namespace nes::assembly::concepts