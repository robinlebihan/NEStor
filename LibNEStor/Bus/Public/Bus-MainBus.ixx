export module NEStor.Bus:MainBus;

import :ExtendedBus;

import NEStor.Common;
import NEStor.RAM;

import <memory>;

namespace nes::bus
{
    export class MainBus : public ExtendedBus<MainBus>
    {
    public:
        struct CreationParams
        {
            std::shared_ptr<ram::RAM> ram;
        };

        explicit MainBus(const CreationParams& params);

        static constexpr Address RamSectionEnd = 0x2000;

        [[nodiscard]] auto ReadByte(Address address) const noexcept -> Byte;
        void               WriteByte(Address address, Byte data) noexcept;

    private:
        std::shared_ptr<ram::RAM> m_ram;
    };

} // namespace nes::bus