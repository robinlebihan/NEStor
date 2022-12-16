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

        EXPECT_CALL(bus, ReadByte(Address{0x1234u})).WillRepeatedly(Return(0x98u));
        EXPECT_CALL(bus, ReadByte(Address{0x1235u})).WillRepeatedly(Return(0x76u));

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

} // namespace nes::cpu::tests