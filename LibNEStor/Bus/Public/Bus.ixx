export module NEStor.Bus;

export import :MainBus;
export import :ExtendedBus;

import NEStor.Common;

import <concepts>;

namespace nes::bus
{
    namespace concepts
    {
        // clang-format off
        export template <typename T>
        concept Bus = requires(T mut_bus, const T bus) {
            { bus.ReadByte(Address{}) }              -> std::same_as<Byte>;
            { mut_bus.WriteByte(Address{}, Byte{}) } -> std::same_as<void>;
        };

        export template <typename T>
        concept ExtendedBus = requires(T mut_bus, const T bus) {
            requires Bus<T>;

            { bus.ReadWord(Address{}) }              -> std::same_as<Word>;
            { mut_bus.WriteWord(Address{}, Word{}) } -> std::same_as<void>;
        };
        // clang-format on

    } // namespace concepts

} // namespace nes::bus
