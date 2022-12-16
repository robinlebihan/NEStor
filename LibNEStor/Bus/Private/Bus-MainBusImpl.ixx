export module NEStor.Bus:MainBusImpl;

import :MainBus;

import NEStor.Common;

namespace nes::bus
{
    MainBus::MainBus(const CreationParams& params)
        : m_ram{params.ram}
    {}

    auto MainBus::ReadByte(Address address) const noexcept -> Byte
    {
        if (address < RamSectionEnd)
        {
            return m_ram->Read(address);
        }

        return 0u;
    }

    void MainBus::WriteByte(Address address, Byte data) noexcept
    {
        if (address < RamSectionEnd)
        {
            m_ram->Write(address, data);
        }
    }

} // namespace nes::bus