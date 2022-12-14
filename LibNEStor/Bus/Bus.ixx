export module NEStor.Bus;

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

    export template <concepts::Bus Bus>
    class BusAdapter
    {
    public:
        explicit BusAdapter(Bus& bus)
            : m_bus{bus}
        {}

        auto ReadByte(Address address) const { return m_bus.ReadByte(address); }
        void WriteByte(Address address, Byte data) { m_bus.WriteByte(address, data); }

        auto ReadWord(Address address) const -> Word
        {
            const Byte lo_byte = ReadByte(address);
            const Byte hi_byte = ReadByte(address + 1);
            return (static_cast<Word>(hi_byte) << 8u) | static_cast<Word>(lo_byte);
        }

        void WriteWord(Address address, Word data)
        {
            const Byte lo_byte = data & 0x00FFu;
            const Byte hi_byte = (data & 0xFF00u) >> 8u;
            WriteByte(address, lo_byte);
            WriteByte(address + 1, hi_byte);
        }

    private:
        Bus& m_bus;
    };

} // namespace nes::bus
