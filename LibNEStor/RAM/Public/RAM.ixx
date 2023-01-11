export module NEStor.RAM;

import NEStor.Common;

import <array>;

namespace nes::ram
{
    [[nodiscard]] constexpr auto ToRAMAddress(Address address) -> Address
    {
        return address & 0x7FF;
    }

    export class RAM
    {
    public:
        constexpr RAM() noexcept = default;

        [[nodiscard]] constexpr auto Read(Address address) const noexcept -> Byte
        {
            return m_memory[ToRAMAddress(address)];
        }

        constexpr void Write(Address address, Byte data) noexcept
        {
            m_memory[ToRAMAddress(address)] = data;
        }

    private:
        std::array<Byte, 0x800> m_memory;
    };

} // namespace nes::ram