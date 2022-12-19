export module NEStor.CPU:StatusFlags;

import NEStor.Common;

import <bitset>;

namespace nes::cpu
{
    export enum class StatusFlag : std::size_t
    {
        Carry            = 0,
        Zero             = 1,
        InterruptDisable = 2,
        Decimal          = 3,
        Overflow         = 6,
        Negative         = 7
    };

    export class StatusRegister
    {
    public:
        [[nodiscard]] constexpr auto GetValue() const noexcept { return m_flags.to_ulong(); }

        constexpr void SetFlag(StatusFlag flag, bool value) noexcept
        {
            m_flags.set(std::to_underlying(flag), value);
        }

        [[nodiscard]] constexpr auto GetFlag(StatusFlag flag) const noexcept
        {
            return m_flags.test(std::to_underlying(flag));
        }

        constexpr void ToggleFlag(StatusFlag flag) noexcept
        {
            m_flags.flip(std::to_underlying(flag));
        }

        friend [[nodiscard]] constexpr auto operator==(const StatusRegister& lhs, const StatusRegister& rhs)
        {
            return lhs.m_flags == rhs.m_flags;
        }

    private:
        std::bitset<8u> m_flags;
    };

} // namespace nes::cpu