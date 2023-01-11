export module NEStor.CPU:EffectiveAddress;

import :State;

import NEStor.Common;
import NEStor.Assembly;
import NEStor.Bus;

namespace nes::cpu
{
    [[nodiscard]] constexpr auto AreAddressesOnSamePage(Address lhs, Address rhs) -> bool
    {
        return (lhs & 0xFF00u) == (rhs & 0xFF00u);
    }

    export struct EffectiveAddress
    {
        Address address;
        bool    crossed_page_boundary;
    };

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::Absolute& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& /*state*/)
        -> EffectiveAddress
    {
        return {.address = address_mode.operand, .crossed_page_boundary = false};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::AbsoluteX& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        const Address effective_address = address_mode.operand + static_cast<Address>(state.x);
        return {.address               = effective_address,
                .crossed_page_boundary = not AreAddressesOnSamePage(address_mode.operand, effective_address)};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::AbsoluteY& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        const Address effective_address = address_mode.operand + static_cast<Address>(state.y);
        return {.address               = effective_address,
                .crossed_page_boundary = not AreAddressesOnSamePage(address_mode.operand, effective_address)};
    }

    [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::Indirect& address_mode,
                                                         const bus::concepts::ExtendedBus auto& bus,
                                                         const CPUState& /*state*/)
        -> EffectiveAddress
    {
        const Address address = bus.ReadWord(address_mode.operand);
        return {.address = address, .crossed_page_boundary = false};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::IndirectX& address_mode,
                                                                const bus::concepts::ExtendedBus auto& bus,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        const Address indirect_address = (address_mode.operand + state.x) % 256u;
        const Address address          = bus.ReadWord(indirect_address);
        return {.address = address, .crossed_page_boundary = false};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::IndirectY& address_mode,
                                                                const bus::concepts::ExtendedBus auto& bus,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        const Address address = bus.ReadWord(static_cast<Address>(address_mode.operand));
        const Address incremented_address = address + static_cast<Address>(state.y);
        return {.address               = incremented_address,
                .crossed_page_boundary = not AreAddressesOnSamePage(address, incremented_address)};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::Zeropage& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& /*state*/)
        -> EffectiveAddress
    {
        return {.address = static_cast<Address>(address_mode.operand), .crossed_page_boundary = false};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::ZeropageX& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        return {.address               = (static_cast<Address>(address_mode.operand) + state.x) % 256u,
                .crossed_page_boundary = false};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::ZeropageY& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        return {.address               = (static_cast<Address>(address_mode.operand) + state.y) % 256u,
                .crossed_page_boundary = false};
    }

    export [[nodiscard]] constexpr auto ComputeEffectiveAddress(const assembly::Relative& address_mode,
                                                                const bus::concepts::ExtendedBus auto& /*bus*/,
                                                                const CPUState& state)
        -> EffectiveAddress
    {
        const Address address = state.program_counter + static_cast<std::int8_t>(address_mode.operand);

        return {.address               = address,
                .crossed_page_boundary = not AreAddressesOnSamePage(address, state.program_counter)};
    }

    namespace concepts
    {
        // clang-format off

        export template <typename T, typename Bus>
        concept MemoryAddressMode = requires(const T address_mode, const Bus bus) {
            { ComputeEffectiveAddress(address_mode, bus, CPUState{}) } -> std::same_as<EffectiveAddress>;
        };

        // clang-format on

    } // namespace concepts

} // namespace nes::cpu
