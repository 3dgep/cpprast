#pragma once

namespace cpprast
{
inline namespace math
{
/// <summary>
/// Returns either a, or b, whichever is less.
/// A faster implementation of min than what is provided by STL.
/// </summary>
/// <typeparam name="T">The value type.</typeparam>
/// <param name="a">The first value.</param>
/// <param name="b">The second value.</param>
/// <returns>Either a, or b, whichever is less.</returns>
template<typename T>
constexpr T min( T a, T b ) noexcept
{
    return a < b ? a : b;
}

/// <summary>
/// Returns either a or b, whichever is greater.
/// This should be a faster implementation than what is provided by STL.
/// </summary>
/// <typeparam name="T">The value type.</typeparam>
/// <param name="a">The first value.</param>
/// <param name="b">The second value.</param>
/// <returns>Either a, or b, whichever is greater.</returns>
template<typename T>
constexpr T max( T a, T b ) noexcept
{
    return a > b ? a : b;
}

/// <summary>
/// Clamp the value `v` between `minVal` and `maxVal`.
/// This should be a faster implementation of clamp than what is provided by STL.
/// </summary>
/// <typeparam name="T">The value type to clamp</typeparam>
/// <param name="v">The value to clamp.</param>
/// <param name="minVal">The minimum allowed value.</param>
/// <param name="maxVal">The maximum allowed value.</param>
/// <returns>The result of clamping `v` between `min`, and `max`.</returns>
template<typename T>
constexpr T clamp( T v, T minVal, T maxVal ) noexcept
{
    return min( max( v, minVal ), maxVal );
}

// Fast modulo for positive numbers - much faster than division-based approach
constexpr int fast_positive_mod( int x, int divisor ) noexcept
{
    // For power-of-2 divisors, use bitwise AND (extremely fast)
    if ( ( divisor & ( divisor - 1 ) ) == 0 )
    {
        return x & ( divisor - 1 );
    }

    // For non-power-of-2, use optimized modulo
    // This avoids the expensive division in the original fast_mod
    return x >= 0 ? x % divisor : ( divisor + ( x % divisor ) ) % divisor;
}

// Optimized floor that works well for typical coordinate ranges
constexpr int fast_floor_int( float x ) noexcept
{
    const int i = static_cast<int>( x );
    return i - ( x < i );  // Branchless: subtract 1 if x was negative and truncated up
}

// Fast modulo that handles negative numbers correctly
constexpr int fast_mod_signed( int x, int divisor ) noexcept
{
    if ( x >= 0 )
    {
        return fast_positive_mod( x, divisor );
    }
    else
    {
        // Handle negative case: make it positive, then mod
        const int pos_mod = fast_positive_mod( -x, divisor );
        return pos_mod == 0 ? 0 : divisor - pos_mod;
    }
}

// Floor division that works correctly with negative numbers
constexpr int floor_div( int x, int divisor ) noexcept
{
    return ( x / divisor ) - ( x % divisor != 0 && ( ( x < 0 ) ^ ( divisor < 0 ) ) );
}

// Mirror coordinate calculation that works for both positive and negative coords
constexpr int mirror_coord( int coord, int size ) noexcept
{
    // Get the tile number (which reflection we're in)
    const int tile = floor_div( coord, size );

    // Get position within the tile [0, size-1]
    int pos = coord - tile * size;  // This is equivalent to proper floor modulo

    // If we're in an odd tile, flip the coordinate
    if ( tile & 1 )
    {
        pos = size - 1 - pos;
    }

    return pos;
}

}  // namespace math

}  // namespace cpprast