#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

import NEStor.Assembly;
import NEStor.Common;

namespace nes::assembly::tests
{
    namespace
    {
        template <typename Instr>
        auto InstructionEq(const Instr& instr)
        {
            return ::testing::VariantWith<Instr>(instr);
        }

    } // namespace

    TEST(AssemblyDecode, AndImmediate)
    {
        // GIVEN
        constexpr Byte opcode  = 0x29;
        constexpr Word operand = 0x7698;

        // WHEN
        constexpr auto decoded = Decode(opcode, operand);

        // THEN
        EXPECT_THAT(decoded, InstructionEq(AndImmediate{0x98}));
        EXPECT_EQ(decoded.GetSize(), 2);
    }

    TEST(AssemblyDecode, BrkImplied)
    {
        // GIVEN
        constexpr Byte opcode  = 0x00;
        constexpr Word operand = 0x9876;

        // WHEN
        constexpr auto decoded = Decode(opcode, operand);

        // THEN
        EXPECT_THAT(decoded, InstructionEq(BrkImplied{}));
        EXPECT_EQ(decoded.GetSize(), 1);
    }

    TEST(AssemblyDecode, JmpAbsolute)
    {
        // GIVEN
        constexpr Byte opcode  = 0x4C;
        constexpr Word operand = 0x3452;

        // WHEN
        constexpr auto decoded = Decode(opcode, operand);

        // THEN
        EXPECT_THAT(decoded, InstructionEq(JmpAbsolute{0x3452}));
        EXPECT_EQ(decoded.GetSize(), 3);
    }

    TEST(AssemblyDecode, UnknownInstruction)
    {
        // GIVEN
        constexpr Byte opcode  = 0x02;
        constexpr Word operand = 0x1234;

        // WHEN
        constexpr auto decoded = Decode(opcode, operand);

        // THEN
        EXPECT_FALSE(decoded.IsValid());
        EXPECT_EQ(decoded.GetSize(), 1);
    }

} // namespace nes::assembly::tests