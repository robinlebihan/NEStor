export module NEStor.CPU;

export import :State;
export import :Execution;
import :Impl;

import NEStor.Bus;

import <concepts>;

namespace nes::cpu
{
    namespace concepts
    {
        // clang-format off
        export template <typename T, typename Bus>
        concept CPU = requires(const T cpu, T mut_cpu, Bus bus) {
            requires bus::concepts::Bus<Bus>;

            { mut_cpu.Update(bus) } -> std::same_as<void>;
            { cpu.GetState() } -> std::same_as<CPUState>;
        };
        // clang-format on

    } // namespace concepts

    export template <bus::concepts::Bus Bus>
    [[nodiscard]] constexpr auto MakeCPU() -> concepts::CPU<Bus> auto
    {
        return CPU<Bus>{};
    }

} // namespace nes::cpu
