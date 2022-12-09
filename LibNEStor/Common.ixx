module;

#include <cstdlib>
#include <cstdint>

export module NEStor.Common;

namespace std
{
    export using std::uint8_t;
    export using std::uint16_t;
    export using std::size_t;

} // namespace std

namespace nes
{
    export using Byte = std::uint8_t;
    export using Word = std::uint16_t;
    export using Address = Word;

} // namespace nes