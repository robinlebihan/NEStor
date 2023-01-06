#include <gtest/gtest.h>
#include <gmock/gmock.h>

import NEStor.Common;
import NEStor.CPU;
import NEStor.Assembly;
import NEStor.Bus;

namespace nes::cpu::tests
{
    using ::testing::StrictMock;
    using ::testing::Return;

    class BusMock : public bus::ExtendedBus<BusMock>
    {
    public:
        MOCK_METHOD(void, WriteByte, (Address, Byte), ());
        MOCK_METHOD(Byte, ReadByte, (Address), (const));
    };

    TEST(CPU, ExecuteJmpAbsolute)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{};

        // WHEN
        const auto cycles = Execute(assembly::JmpAbsolute{0x1234u}, state, bus);

        // THEN
        EXPECT_EQ(state.program_counter, 0x1234u);
        EXPECT_EQ(cycles, 3);
    }

    TEST(CPU, ExecuteJmpIndirect)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{};

        EXPECT_CALL(bus, ReadByte(Address{0x1234u})).WillRepeatedly(Return(Byte{0x98u}));
        EXPECT_CALL(bus, ReadByte(Address{0x1235u})).WillRepeatedly(Return(Byte{0x76u}));

        // WHEN
        const auto cycles = Execute(assembly::JmpIndirect{0x1234u}, state, bus);

        // THEN
        EXPECT_EQ(state.program_counter, 0x7698u);
        EXPECT_EQ(cycles, 5);
    }

    TEST(CPU, ExecuteAndAbsoluteX)
    {
        // GIVEN
        constexpr Byte accumulator = 0xF4u;
        constexpr Byte operand     = 0xF3u;

        StrictMock<BusMock> bus;
        CPUState            state{.accumulator = accumulator, .x = 1u};

        EXPECT_CALL(bus, ReadByte(Address{0x2000u})).WillRepeatedly(Return(operand));

        // WHEN
        const auto cycles = Execute(assembly::AndAbsoluteX{0x1FFFu}, state, bus);

        // THEN
        EXPECT_EQ(state.accumulator, accumulator & operand);
        EXPECT_FALSE(state.status.GetFlag(StatusFlag::Zero));
        EXPECT_TRUE(state.status.GetFlag(StatusFlag::Negative));
        EXPECT_EQ(cycles, assembly::AndAbsoluteX::Metadata.cycles + 1);
    }

    TEST(CPU, ExecuteBccRelative)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{.program_counter = 0x2000u};

        // WHEN
        const auto cycles = Execute(assembly::BccRelative{static_cast<Byte>(-5)}, state, bus);

        // THEN
        EXPECT_EQ(state.program_counter, 0x1FFBu);
        EXPECT_EQ(cycles, assembly::BccRelative::Metadata.cycles + 2);
    }

    TEST(CPU, ExecuteLdaImmediate)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{};

        // WHEN
        const auto cycles = Execute(assembly::LdaImmediate{0xF8}, state, bus);

        // THEN
        EXPECT_EQ(state.accumulator, 0xF8);
        EXPECT_FALSE(state.status.GetFlag(StatusFlag::Zero));
        EXPECT_TRUE(state.status.GetFlag(StatusFlag::Negative));
        EXPECT_EQ(cycles, assembly::LdaImmediate::Metadata.cycles);
    }

    TEST(CPU, ExecuteTaxImplied)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{.accumulator = 0xF3, .x = 0x23};

        // WHEN
        const auto cycles = Execute(assembly::TaxImplied{}, state, bus);

        // THEN
        EXPECT_EQ(state.accumulator, 0xF3);
        EXPECT_EQ(state.x, 0xF3);
        EXPECT_EQ(cycles, assembly::TaxImplied::Metadata.cycles);
    }

    TEST(CPU, ExecuteClcImplied)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{};
        state.status.SetFlag(StatusFlag::Carry, true);

        // WHEN
        const auto cycles = Execute(assembly::ClcImplied{}, state, bus);

        // THEN
        EXPECT_FALSE(state.status.GetFlag(StatusFlag::Carry));
        EXPECT_EQ(cycles, assembly::ClcImplied::Metadata.cycles);
    }

    TEST(CPU, ExecuteStaAbsolute)
    {
        // GIVEN
        constexpr Byte AccumulatorValue = 0xF8u;

        StrictMock<BusMock> bus;
        CPUState            state{.accumulator = AccumulatorValue};

        EXPECT_CALL(bus, WriteByte(Address{0xBEEFu}, AccumulatorValue));

        // WHEN
        const auto cycles = Execute(assembly::StaAbsolute{0xBEEFu}, state, bus);

        // THEN
        EXPECT_EQ(cycles, assembly::StaAbsolute::Metadata.cycles);
    }

    TEST(CPU, ExecuteDexImplied)
    {
        // GIVEN
        StrictMock<BusMock> bus;
        CPUState            state{.x = 0x34};

        // WHEN
        const auto cycles = Execute(assembly::DexImplied{}, state, bus);

        // THEN
        EXPECT_EQ(state.x, 0x33);
        EXPECT_EQ(cycles, assembly::DexImplied::Metadata.cycles);
    }

} // namespace nes::cpu::tests