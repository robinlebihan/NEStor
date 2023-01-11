module;

#include <gmock/gmock.h>

export module NEStor.Tests.Mocks;

import NEStor.Common;
import NEStor.Bus;

namespace nes::mocks
{
    export class BusMock : public bus::ExtendedBus<BusMock>
    {
    public:
        MOCK_METHOD(void, WriteByte, (Address, Byte), ());
        MOCK_METHOD(Byte, ReadByte, (Address), (const));
    };

} // namespace nes::mocks