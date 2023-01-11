export module NEStor.Bus:ExtendedBus;

import NEStor.Common;

namespace nes::bus
{
    export template <typename Bus>
    class ExtendedBus
    {
    public:
        auto ReadWord(Address address) const -> Word
        {
            const auto& self = static_cast<const Bus&>(*this);

            const Byte lo_byte = self.ReadByte(address);
            const Byte hi_byte = self.ReadByte(address + 1);
            return (static_cast<Word>(hi_byte) << 8u) | static_cast<Word>(lo_byte);
        }

        void WriteWord(Address address, Word data)
        {
            auto& self = static_cast<Bus&>(*this);

            const Byte lo_byte = data & 0x00FFu;
            const Byte hi_byte = (data & 0xFF00u) >> 8u;
            self.WriteByte(address, lo_byte);
            self.WriteByte(address + 1, hi_byte);
        }
    };

} // namespace nes::bus
