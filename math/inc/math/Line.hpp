#pragma once

#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

namespace cpprast
{
inline namespace math
{
struct Line
{
    explicit Line( const glm::vec2& p0 = glm::vec2 { 0 }, const glm::vec2& p1 = glm::vec2 { 0 } )
    : p0 { p0 }
    , p1 { p1 }
    {}

    /// <summary>
    /// Get the length of the line.
    /// </summary>
    /// <returns>The length of the line.</returns>
    [[nodiscard]] float length() const
    {
        return distance( p0, p1 );
    }

    /// <summary>
    /// Compute the closest point on this line to a point.
    /// </summary>
    /// <param name="p">The point to test.</param>
    /// <returns>The closest point on this line to `p`.</returns>
    [[nodiscard]] glm::vec2 closestPoint( const glm::vec2& p ) const
    {
        const glm::vec2 ab = p1 - p0;              // ab
        const float     f  = glm::dot( ab, ab );

        // Degenerate segment: both endpoints are the same point.
        if ( f <= 0.0f )
            return p0;

        // Project p onto ab, computing parameterized position d(t) = a + t * (b - a)
        float t = glm::dot( p - p0, ab ) / f;
        // Clamp t to the closest endpoint.
        t = glm::clamp( t, 0.0f, 1.0f );
        // Compute the projected position from the clamped t value.
        return p0 + t * ab;
    }

    /// <summary>
    /// Compute the squared distance between this line and a point.
    /// Source: Real-time Collision Detection, Christer Ericson (2005).
    /// </summary>
    /// <param name="p">The point to compute the distance to.</param>
    /// <returns>The squared distance between the point and this line.</returns>
    [[nodiscard]] float squareDistance( const glm::vec2& p ) const
    {
        const glm::vec2 dir   = p1 - p0;  // ab
        const glm::vec2 diff0 = p - p0;   // ac
        const glm::vec2 diff1 = p - p1;   // bc

        const float e = glm::dot( diff0, dir );
        if ( e <= 0.0f )
            return glm::dot( diff0, diff0 );

        const float f = glm::dot( dir, dir );
        if ( e >= f )
            return glm::dot( diff1, diff1 );

        return glm::dot( diff0, diff0 ) - e * e / f;
    }

    glm::vec2 p0 { 0 };
    glm::vec2 p1 { 0 };
};
}  // namespace math
}  // namespace cpprast