#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").


#include <limits>     // INT_MAX
#include <cstdint>     // uint8_t

#include <type_traits>      // std::is_unsigned_v

namespace std {
    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        constexpr inline int log2_8( const uint8_t x ) noexcept {
            constexpr int logs[] = {-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
            return (x & 0xF0 ? 4 + logs[x >> 4] : logs[x]);
        }

        constexpr inline int log2_16( const uint16_t x ) noexcept { 
			return (x & 0xFF00 ? 8 + log2_8( uint8_t( x >> 8 ) ) : log2_8( uint8_t( x ))); 
		}

        constexpr inline int log2_32( const uint32_t x ) noexcept { 
			return (x & 0xFFFF0000 ? 16 + log2_16( uint16_t( x >> 16 ) ) : log2_16( uint16_t( x ) )); 
		}

        constexpr inline int log2_64( const uint64_t x ) noexcept { 
			return (x & 0xFFFFFFFF00000000 ? 32 + log2_32( uint32_t( x >> 32 ) ) : log2_32( uint32_t( x ))); 
		}

        constexpr inline int log2(const uint8_t x ) noexcept  { return log2_8( x ); }
        constexpr inline int log2(const uint16_t x ) noexcept { return log2_16( x ); }
        constexpr inline int log2(const uint32_t x ) noexcept { return log2_32( x ); }
        constexpr inline int log2(const uint64_t x ) noexcept { return log2_64( x ); }
    }  
    template< class Unsigned >
    constexpr inline int intlog2( const Unsigned x ) noexcept {
        static_assert( std::is_unsigned_v<Unsigned> );
        return impl::log2( x );
    }

    /// \brief The position of the least significant bit in an unsigned value, or -1 for value zero.
    // For the general case this is the same as the number of rightmost zeroes.
    //
    template< class Unsigned >
    constexpr inline int intlog2r( const Unsigned x ) noexcept {
        return (x == 0? -1 : impl::log2( Unsigned( x ^ Unsigned(x - 1) ) ));
    }
}  