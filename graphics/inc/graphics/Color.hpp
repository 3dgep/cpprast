#pragma once

#include <math/Math.hpp>

#include <glm/vec3.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <string_view>

namespace cpprast
{
inline namespace graphics
{
union Color
{
    /// <summary>
    /// Construct a default (black) color.
    /// </summary>
    constexpr Color() noexcept;

    /// <summary>
    /// Construct a color from a 32-bit integer.
    /// </summary>
    /// <param name="rgba">The color value as a 32-bit integer (0xAABBGGRR).</param>
    constexpr explicit Color( uint32_t rgba ) noexcept;

    /// <summary>
    /// Construct a color from red, green, and blue color primaries.
    /// </summary>
    /// <param name="r">The red component.</param>
    /// <param name="g">The green component.</param>
    /// <param name="b">The blue component.</param>
    /// <param name="a">The alpha component.</param>
    constexpr Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255u ) noexcept;

    ~Color() noexcept                          = default;
    constexpr Color( const Color& ) noexcept   = default;
    constexpr Color( Color&& ) noexcept        = default;
    constexpr Color& operator=( const Color& ) = default;
    constexpr Color& operator=( Color&& )      = default;

    constexpr auto operator<=>( const Color& rhs ) const noexcept;
    constexpr bool operator==( const Color& rhs ) const noexcept;

    Color  operator+( const Color& rhs ) const noexcept;
    Color& operator+=( const Color& rhs ) noexcept;
    Color  operator-( const Color& rhs ) const noexcept;
    Color& operator-=( const Color& rhs ) noexcept;
    Color  operator*( const Color& rhs ) const noexcept;
    Color& operator*=( const Color& rhs ) noexcept;
    Color  operator*( float rhs ) const noexcept;
    Color& operator*=( float rhs ) noexcept;
    Color  operator/( float rhs ) const noexcept;
    Color& operator/=( float rhs ) noexcept;

    /// <summary>
    /// Return this color with a specified alpha value.
    /// </summary>
    /// <param name="alpha">The alpha value for the new color.</param>
    /// <returns>This color with a give alpha value.</returns>
    constexpr Color withAlpha( uint8_t alpha ) const noexcept;

    /// <summary>
    /// Return this color with a specified alpha value.
    /// </summary>
    /// <param name="alpha">The alpha value for the new color.</param>
    /// <returns>This color with a give alpha value.</returns>
    constexpr Color withAlpha( float alpha ) const noexcept;

    /// <summary>
    /// Construct a color using floating-point values in the range [0 ... 1].
    /// </summary>
    /// <param name="r">The red color component.</param>
    /// <param name="g">The green color component.</param>
    /// <param name="b">The blue color component.</param>
    /// <param name="a">(optional) The alpha component. Default: 1.0f</param>
    /// <returns>The color.</returns>
    static constexpr Color fromFloats( float r, float g, float b, float a = 1.0f ) noexcept;

    /// <summary>
    /// Construct a color from a 32-bit unsigned integer (usually expressed as a hexadecimal value).
    /// The color is expressed as <code>0xAABBGGRR</code>. The alpha channel (<code>AA</code>) can be omitted from the
    /// hexadecimal value, but the default alpha will be 0.<br>
    /// Transparent red is <code>0xFF</code>.<br>
    /// Transparent green is <code>0xFF00</code>.<br>
    /// Transparent blue is <code>0xFF0000</code>.<br>
    /// Opaque black is <code>0xFF000000</code>.<br>
    ///
    /// </summary>
    /// <param name="color">The color as a 32-bit unsigned integer.</param>
    /// <returns>The RGBA color.</returns>
    static constexpr Color fromHex( uint32_t color ) noexcept;

    /// <summary>
    /// Parses an HTML color string and returns the corresponding Color object.
    /// </summary>
    /// <param name="html">A string view containing the HTML color code (e.g., "#FF0000" or "red").</param>
    /// <returns>A Color object representing the parsed color.</returns>
    static Color fromHTML( std::string_view html );

    /// <summary>
    /// Construct a color from Hue, Saturation, and Brightness values.
    /// See: <a href="https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB">HSL and HSV on Wikipedia</a>.
    /// </summary>
    /// <param name="H">Hue in the range [0, 360).</param>
    /// <param name="S">Saturation in the range [0, 1].</param>
    /// <param name="V">Value in the range [0, 1].</param>
    /// <returns>The color constructed from the given HSV values.</returns>
    static inline Color fromHSV( float H, float S = 1.0f, float V = 1.0f ) noexcept;

    uint32_t rgba;
    struct Channels
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } channels;

    /// <summary>
    /// Masks for each of the color channels.
    /// </summary>
    static constexpr uint32_t RedMask   = 0x000000FF;
    static constexpr uint32_t GreenMask = 0x0000FF00;
    static constexpr uint32_t BlueMask  = 0x00FF0000;
    static constexpr uint32_t AlphaMask = 0xFF000000;

    /// <summary>
    /// Bit shifts for each of the color channels.
    /// </summary>
    static constexpr uint32_t RedShift   = 0;
    static constexpr uint32_t GreenShift = 8;
    static constexpr uint32_t BlueShift  = 16;
    static constexpr uint32_t AlphaShift = 24;

    static const Color AliceBlue;
    static const Color AntiqueWhite;
    static const Color Aqua;
    static const Color AquaMarine;
    static const Color Azure;
    static const Color Beige;
    static const Color Bisque;
    static const Color Black;
    static const Color BlanchedAlmond;
    static const Color Blue;
    static const Color BlueViolet;
    static const Color Brown;
    static const Color BurlyWood;
    static const Color CadetBlue;
    static const Color Chartreuse;
    static const Color Chocolate;
    static const Color Coral;
    static const Color CornflowerBlue;
    static const Color Cornsilk;
    static const Color Crimson;
    static const Color Cyan;
    static const Color DarkBlue;
    static const Color DarkCyan;
    static const Color DarkGoldenRod;
    static const Color DarkGray;
    static const Color DarkGrey;
    static const Color DarkGreen;
    static const Color DarkKhaki;
    static const Color DarkMagenta;
    static const Color DarkOliveGreen;
    static const Color DarkOrange;
    static const Color DarkOrchid;
    static const Color DarkRed;
    static const Color DarkSalmon;
    static const Color DarkSeaGreen;
    static const Color DarkSlateBlue;
    static const Color DarkSlateGray;
    static const Color DarkSlateGrey;
    static const Color DarkTurquoise;
    static const Color DarkViolet;
    static const Color DeepPink;
    static const Color DeepSkyBlue;
    static const Color DimGray;
    static const Color DimGrey;
    static const Color DodgerBlue;
    static const Color FireBrick;
    static const Color FloralWhite;
    static const Color ForestGreen;
    static const Color Fuchsia;
    static const Color Gainsboro;
    static const Color GhostWhite;
    static const Color Gold;
    static const Color GoldenRod;
    static const Color Gray;
    static const Color Grey;
    static const Color Green;
    static const Color GreenYellow;
    static const Color HoneyDew;
    static const Color HotPink;
    static const Color IndianRed;
    static const Color Indigo;
    static const Color Ivory;
    static const Color Khaki;
    static const Color Lavender;
    static const Color LavenderBlush;
    static const Color LawnGreen;
    static const Color LemonChiffon;
    static const Color LightBlue;
    static const Color LightCoral;
    static const Color LightCyan;
    static const Color LightGoldenRodYellow;
    static const Color LightGray;
    static const Color LightGrey;
    static const Color LightGreen;
    static const Color LightPink;
    static const Color LightSalmon;
    static const Color LightSeaGreen;
    static const Color LightSkyBlue;
    static const Color LightSlateGray;
    static const Color LightSlateGrey;
    static const Color LightSteelBlue;
    static const Color LightYellow;
    static const Color Lime;
    static const Color LimeGreen;
    static const Color Linen;
    static const Color Magenta;
    static const Color Maroon;
    static const Color MediumAquaMarine;
    static const Color MediumBlue;
    static const Color MediumOrchid;
    static const Color MediumPurple;
    static const Color MediumSeaGreen;
    static const Color MediumSlateBlue;
    static const Color MediumSpringGreen;
    static const Color MediumTurquoise;
    static const Color MediumVioletRed;
    static const Color MidnightBlue;
    static const Color MintCream;
    static const Color MistyRose;
    static const Color Moccasin;
    static const Color NavajoWhite;
    static const Color Navy;
    static const Color OldLace;
    static const Color Olive;
    static const Color OliveDrab;
    static const Color Orange;
    static const Color OrangeRed;
    static const Color Orchid;
    static const Color PaleGoldenRod;
    static const Color PaleGreen;
    static const Color PaleTurquoise;
    static const Color PaleVioletRed;
    static const Color PapayaWhip;
    static const Color PeachPuff;
    static const Color Peru;
    static const Color Pink;
    static const Color Plum;
    static const Color PowderBlue;
    static const Color Purple;
    static const Color RebeccaPurple;
    static const Color Red;
    static const Color RosyBrown;
    static const Color RoyalBlue;
    static const Color SaddleBrown;
    static const Color Salmon;
    static const Color SandyBrown;
    static const Color SeaGreen;
    static const Color Seashell;
    static const Color Sienna;
    static const Color Silver;
    static const Color SkyBlue;
    static const Color SlateBlue;
    static const Color SlateGray;
    static const Color SlateGrey;
    static const Color Snow;
    static const Color SpringGreen;
    static const Color SteelBlue;
    static const Color Tan;
    static const Color Teal;
    static const Color Thistle;
    static const Color Tomato;
    static const Color Turquoise;
    static const Color Violet;
    static const Color Wheat;
    static const Color White;
    static const Color WhiteSmoke;
    static const Color Yellow;
    static const Color YellowGreen;
};

constexpr Color::Color() noexcept
: channels { 0, 0, 0, 255 }
{}

constexpr Color::Color( uint32_t rgba ) noexcept
: rgba { rgba }
{}

constexpr Color::Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) noexcept
: channels { r, g, b, a }
{}

constexpr bool Color::operator==( const Color& rhs ) const noexcept
{
    return rgba == rhs.rgba;
}

constexpr auto Color::operator<=>( const Color& rhs ) const noexcept
{
    if ( const auto cmp = channels.r <=> rhs.channels.r; cmp != 0 )
        return cmp;
    if ( const auto cmp = channels.g <=> rhs.channels.g; cmp != 0 )
        return cmp;
    if ( const auto cmp = channels.b <=> rhs.channels.b; cmp != 0 )
        return cmp;

    return channels.a <=> rhs.channels.a;
}

inline Color Color::operator+( const Color& rhs ) const noexcept
{
    const auto red   = static_cast<uint8_t>( math::min( channels.r + rhs.channels.r, 255 ) );
    const auto green = static_cast<uint8_t>( math::min( channels.g + rhs.channels.g, 255 ) );
    const auto blue  = static_cast<uint8_t>( math::min( channels.b + rhs.channels.b, 255 ) );
    const auto alpha = static_cast<uint8_t>( math::min( channels.a + rhs.channels.a, 255 ) );

    return { red, green, blue, alpha };
}

inline Color& Color::operator+=( const Color& rhs ) noexcept
{
    *this = *this + rhs;
    return *this;
}

inline Color Color::operator-( const Color& rhs ) const noexcept
{
    const auto red   = static_cast<uint8_t>( math::max( channels.r - rhs.channels.r, 0 ) );
    const auto green = static_cast<uint8_t>( math::max( channels.g - rhs.channels.g, 0 ) );
    const auto blue  = static_cast<uint8_t>( math::max( channels.b - rhs.channels.b, 0 ) );
    const auto alpha = static_cast<uint8_t>( math::max( channels.a - rhs.channels.a, 0 ) );

    return { red, green, blue, alpha };
}

inline Color& Color::operator-=( const Color& rhs ) noexcept
{
    *this = *this - rhs;
    return *this;
}

inline Color Color::operator*( const Color& rhs ) const noexcept
{
    const auto red   = static_cast<uint8_t>( channels.r * rhs.channels.r / 255 );
    const auto green = static_cast<uint8_t>( channels.g * rhs.channels.g / 255 );
    const auto blue  = static_cast<uint8_t>( channels.b * rhs.channels.b / 255 );
    const auto alpha = static_cast<uint8_t>( channels.a * rhs.channels.a / 255 );

    return { red, green, blue, alpha };
}

inline Color& Color::operator*=( const Color& rhs ) noexcept
{
    *this = *this * rhs;
    return *this;
}

inline Color Color::operator*( float rhs ) const noexcept
{
    const auto red   = static_cast<uint8_t>( math::clamp( static_cast<float>( channels.r ) * rhs, 0.0f, 255.0f ) );
    const auto green = static_cast<uint8_t>( math::clamp( static_cast<float>( channels.g ) * rhs, 0.0f, 255.0f ) );
    const auto blue  = static_cast<uint8_t>( math::clamp( static_cast<float>( channels.b ) * rhs, 0.0f, 255.0f ) );
    const auto alpha = static_cast<uint8_t>( math::clamp( static_cast<float>( channels.a ) * rhs, 0.0f, 255.0f ) );

    return { red, green, blue, alpha };
}

inline Color& Color::operator*=( float rhs ) noexcept
{
    *this = *this * rhs;
    return *this;
}

inline Color Color::operator/( float rhs ) const noexcept
{
    assert( rhs != 0.0f );

    rhs = 1.0f / rhs;

    return operator*( rhs );
}

inline Color& Color::operator/=( float rhs ) noexcept
{
    assert( rhs != 0.0f );

    rhs = 1.0f / rhs;

    return operator*=( rhs );
}

constexpr Color Color::withAlpha( uint8_t alpha ) const noexcept
{
    return { channels.r, channels.g, channels.b, alpha };
}

constexpr Color Color::withAlpha( float alpha ) const noexcept
{
    return withAlpha( static_cast<uint8_t>( math::clamp( alpha * 255.0f, 0.0f, 255.0f ) ) );
}

constexpr Color Color::fromFloats( float r, float g, float b, float a ) noexcept
{
    const auto red   = static_cast<uint8_t>( math::clamp( r * 255.0f, 0.0f, 255.0f ) );
    const auto green = static_cast<uint8_t>( math::clamp( g * 255.0f, 0.0f, 255.0f ) );
    const auto blue  = static_cast<uint8_t>( math::clamp( b * 255.0f, 0.0f, 255.0f ) );
    const auto alpha = static_cast<uint8_t>( math::clamp( a * 255.0f, 0.0f, 255.0f ) );

    return { red, green, blue, alpha };
}

constexpr Color Color::fromHex( uint32_t color ) noexcept
{
    const auto r = static_cast<uint8_t>( ( color & RedMask ) >> RedShift );
    const auto g = static_cast<uint8_t>( ( color & GreenMask ) >> GreenShift );
    const auto b = static_cast<uint8_t>( ( color & BlueMask ) >> BlueShift );
    const auto a = static_cast<uint8_t>( ( color & AlphaMask ) >> AlphaShift );

    return { r, g, b, a };
}

Color Color::fromHSV( float H, float S, float V ) noexcept
{
    // Ensure H is within [0, 360)
    H = fmodf( H, 360.0f );
    if ( H < 0 )
        H += 360.0f;

    S = math::clamp( S, 0.0f, 1.0f );
    V = math::clamp( V, 0.0f, 1.0f );

    float C  = V * S;
    float m  = V - C;
    float H2 = H / 60.0f;
    float X  = C * ( 1.0f - fabsf( fmodf( H2, 2.0f ) - 1.0f ) );

    float r = 0, g = 0, b = 0;

    switch ( static_cast<int>( H2 ) )
    {
    case 0:
        r = C;
        g = X;
        b = 0;
        break;
    case 1:
        r = X;
        g = C;
        b = 0;
        break;
    case 2:
        r = 0;
        g = C;
        b = X;
        break;
    case 3:
        r = 0;
        g = X;
        b = C;
        break;
    case 4:
        r = X;
        g = 0;
        b = C;
        break;
    case 5:
        r = C;
        g = 0;
        b = X;
        break;
    default:
        r = 0;
        g = 0;
        b = 0;
        break;
    }

    r += m;
    g += m;
    b += m;

    return fromFloats( r, g, b );
}

inline Color operator*( float lhs, const Color& rhs )
{
    return rhs * lhs;
}

/// <summary>
/// Returns the component-wise minimum of two colors.
/// </summary>
/// <param name="c1">The first color.</param>
/// <param name="c2">The second color.</param>
/// <returns>The component-wise minimum of the two colors.</returns>
inline Color min( const Color& c1, const Color& c2 )
{
    const auto r = math::min( c1.channels.r, c2.channels.r );
    const auto g = math::min( c1.channels.g, c2.channels.g );
    const auto b = math::min( c1.channels.b, c2.channels.b );
    const auto a = math::min( c1.channels.a, c2.channels.a );

    return { r, g, b, a };
}

/// <summary>
/// Returns the component-wise maximum of two colors.
/// </summary>
/// <param name="c1">The first color.</param>
/// <param name="c2">The second color.</param>
/// <returns>The component-wise maximum of the two colors.</returns>
inline Color max( const Color& c1, const Color& c2 )
{
    const auto r = math::max( c1.channels.r, c2.channels.r );
    const auto g = math::max( c1.channels.g, c2.channels.g );
    const auto b = math::max( c1.channels.b, c2.channels.b );
    const auto a = math::max( c1.channels.a, c2.channels.a );

    return { r, g, b, a };
}

inline Color interpolate( const Color& c0, const Color& c1, const Color& c2, const glm::vec3& bc )
{
    // c = c0 * bc.x
    float r = static_cast<float>( c0.channels.r ) * bc.x;
    float g = static_cast<float>( c0.channels.g ) * bc.x;
    float b = static_cast<float>( c0.channels.b ) * bc.x;
    float a = static_cast<float>( c0.channels.a ) * bc.x;

    // c += c1 * bc.y
    r = std::fma<float>( c1.channels.r, bc.y, r );
    g = std::fma<float>( c1.channels.g, bc.y, g );
    b = std::fma<float>( c1.channels.b, bc.y, b );
    a = std::fma<float>( c1.channels.a, bc.y, a );

    // c += c2 * bc.z
    r = std::fma<float>( c2.channels.r, bc.z, r );
    g = std::fma<float>( c2.channels.g, bc.z, g );
    b = std::fma<float>( c2.channels.b, bc.z, b );
    a = std::fma<float>( c2.channels.a, bc.z, a );

    return {
        static_cast<uint8_t>( r ),
        static_cast<uint8_t>( g ),
        static_cast<uint8_t>( b ),
        static_cast<uint8_t>( a )
    };
}

static_assert( sizeof( Color ) == sizeof( uint32_t ) );
}  // namespace graphics
}  // namespace cpprast