module;

#include <cstdlib>
#include <cstdint>

export module NEStor.Common;

import <type_traits>;

namespace std
{
    export using std::uint8_t;
    export using std::uint16_t;
    export using std::uint64_t;
    export using std::size_t;

} // namespace std

namespace nes
{
    export using Byte = std::uint8_t;
    export using Word = std::uint16_t;
    export using Address = Word;

    /*
    * XXX: phoney function to use when checking the type of a class/struct member inside a concept
    * Otherwise the type of the member will have an extra unwanted reference.
    *
    * TODO: P0849R8 of C++23 avoids having this function, but it is not yet implemented in MSVC.
    */
    export template <class T>
    std::decay_t<T> decay_copy(T&&);

} // namespace nes