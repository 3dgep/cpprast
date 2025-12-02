#pragma once

#include "Viewport.hpp"

#include <glm/common.hpp>  // For glm::min/glm::max
#include <glm/vec2.hpp>

#include <limits>
#include <optional>

namespace cpprast
{
inline namespace math
{
struct AABB
{
    AABB()                                  = default;
    ~AABB()                                 = default;
    AABB( const AABB& ) noexcept            = default;
    AABB( AABB&& ) noexcept                 = default;
    AABB& operator=( const AABB& ) noexcept = default;
    AABB& operator=( AABB&& ) noexcept      = default;

    /// <summary>
    /// Construct an axis-aligned bounding box from 2 points.
    /// </summary>
    /// <param name="a">The first point.</param>
    /// <param name="b">The second point.</param>
    AABB( const glm::vec2& a, const glm::vec2& b ) noexcept
    {
        min = glm::min( a, b );
        max = glm::max( a, b );
    }

    /// <summary>
    /// Construct an axis-aligned bounding box from 3 points.
    /// </summary>
    /// <param name="a">The first point.</param>
    /// <param name="b">The second point.</param>
    /// <param name="c">The third point.</param>
    AABB( const glm::vec2& a, const glm::vec2& b, const glm::vec2& c ) noexcept
    {
        min = glm::min( a, glm::min( b, c ) );
        max = glm::max( a, glm::max( b, c ) );
    }

    /// <summary>
    /// Construct an axis-aligned bounding box from 4 2D points.
    /// </summary>
    /// <param name="a">The first point.</param>
    /// <param name="b">The second point.</param>
    /// <param name="c">The third point.</param>
    /// <param name="d">The fourth point.</param>
    AABB( const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& d ) noexcept
    {
        min = glm::min( glm::min( a, b ), glm::min( c, d ) );
        max = glm::max( glm::max( a, b ), glm::max( c, d ) );
    }

    /// <summary>
    /// Construct an axis-aligned bounding box from a viewport.
    /// </summary>
    /// <param name="viewport">The viewport used to construct the AABB.</param>
    explicit AABB( const math::Viewport& viewport )
    {
        min = glm::vec2 { viewport.x, viewport.y };
        max = glm::vec2 { viewport.x + viewport.width - 1, viewport.y + viewport.height - 1 };
    }

    /// <summary>
    /// Translate this AABB.
    /// </summary>
    /// <param name="rhs">The amount to translate this AABB by.</param>
    /// <returns>The translated AABB.</returns>
    AABB operator+( const glm::vec2& rhs ) const noexcept
    {
        return { min + rhs, max + rhs };
    }

    /// <summary>
    /// Translate this AABB.
    /// </summary>
    /// <param name="rhs">The amount to translate this AABB by.</param>
    /// <returns>A reference to this AABB after translation.</returns>
    AABB& operator+=( const glm::vec2& rhs ) noexcept
    {
        min += rhs;
        max += rhs;

        return *this;
    }

    /// <summary>
    /// Translate this AABB.
    /// </summary>
    /// <param name="rhs">The amount to translate this AABB by.</param>
    /// <returns>The translated AABB.</returns>
    AABB operator-( const glm::vec2& rhs ) const noexcept
    {
        return { min - rhs, max - rhs };
    }

    /// <summary>
    /// Translate this AABB.
    /// </summary>
    /// <param name="rhs">The amount to translate this AABB by.</param>
    /// <returns>A reference to this AABB after translation.</returns>
    AABB& operator-=( const glm::vec2& rhs ) noexcept
    {
        min -= rhs;
        max -= rhs;

        return *this;
    }

    /// <summary>
    /// Check to see if this is a valid AABB.
    /// The min point of a valid AABB is less than the max point.
    /// </summary>
    /// <returns>true if the min point is less than the max point.</returns>
    bool isValid() const noexcept
    {
        return glm::all( glm::lessThan( min, max ) );
    }

    /// <summary>
    /// Returns the left (minimum x) coordinate.
    /// </summary>
    /// <returns>The left (minimum x) coordinate of the AABB.</returns>
    float left() const noexcept
    {
        return min.x;
    }

    /// <summary>
    /// Returns the rightmost x-coordinate value.
    /// </summary>
    /// <returns>The right (maximum x) coordinate of the AABB.</returns>
    float right() const noexcept
    {
        return max.x;
    }

    /// <summary>
    /// Returns the top (minimum y-coordinate) value.
    /// </summary>
    /// <returns>The top (minimum y) coordinate of the AABB.</returns>
    float top() const noexcept
    {
        return min.y;
    }

    /// <summary>
    /// Returns the bottom coordinate (y value) of the object.
    /// </summary>
    /// <returns>The bottom (maximum y) coordinate of the AABB.</returns>
    float bottom() const noexcept
    {
        return max.y;
    }

    /// <summary>
    /// Compute the center point of the AABB.
    /// </summary>
    /// <returns>The center point of the AABB.</returns>
    glm::vec2 center() const noexcept
    {
        return ( min + max ) * 0.5f;
    }

    /// <summary>
    /// Get the width (along the x-axis) of the AABB.
    /// </summary>
    /// <returns>The width of the AABB.</returns>
    float width() const noexcept
    {
        return max.x - min.x;
    }

    /// <summary>
    /// Get the height (along the y-axis) of the AABB.
    /// </summary>
    /// <returns>The height of the AABB.</returns>
    float height() const noexcept
    {
        return max.y - min.y;
    }

    /// <summary>
    /// Compute the 2D area of the AABB (width x height).
    /// </summary>
    /// <returns>The 2D area of the AABB.</returns>
    float area() const noexcept
    {
        return width() * height();
    }

    /// <summary>
    /// Compute the size of the AABB.
    /// </summary>
    /// <returns>Returns the vector from the min to the max point.</returns>
    glm::vec2 size() const noexcept
    {
        return max - min;
    }

    /// <summary>
    /// Compute the extent of the AABB.
    /// The extent is 1/2 the size of the AABB.
    /// </summary>
    /// <returns></returns>
    glm::vec2 extent() const noexcept
    {
        return size() * 0.5f;
    }

    /// <summary>
    /// Expand the AABB to include a given point.
    /// </summary>
    /// <param name="p"></param>
    AABB& expand( const glm::vec2& p ) noexcept
    {
        min = glm::min( min, p );
        max = glm::max( max, p );

        return *this;
    }

    /// <summary>
    /// Expand this AABB by another AABB.
    /// </summary>
    /// <param name="aabb">The other ABB to expand this one.</param>
    AABB& expand( const AABB& aabb ) noexcept
    {
        min = glm::min( min, aabb.min );
        max = glm::max( max, aabb.max );

        return *this;
    }

    /// <summary>
    /// Clamp this AABB by another AABB.
    /// Warning: This could result in invalid AABB if the min point becomes larger than the max point.
    /// Use the <see cref="AABB::isValid"/> method to test if the AABB is still valid after clamping.
    /// </summary>
    /// <param name="aabb">The AABB to clamp this one to.</param>
    AABB& clamp( const AABB& aabb ) noexcept
    {
        min = glm::max( min, aabb.min );
        max = glm::min( max, aabb.max );

        return *this;
    }

    /// <summary>
    /// Return this AABB clamped to another.
    /// </summary>
    AABB clamped( const AABB& aabb ) const noexcept
    {
        return fromMinMax( glm::max( min, aabb.min ), glm::min( max, aabb.max ) );
    }

    /// <summary>
    /// Check to see if another AABB intersects with this one.
    /// </summary>
    /// <param name="aabb">The other AABB to check for intersection.</param>
    /// <returns>`true` if the AABBs intersect, `false` otherwise.</returns>
    bool intersect( const AABB& aabb ) const noexcept
    {
        return glm::all( glm::lessThanEqual( min, aabb.max ) ) && glm::all( glm::greaterThanEqual( max, aabb.min ) );
    }

    /// <summary>
    /// Test whether a point is contained in this AABB.
    /// </summary>
    /// <param name="p">The point to test for containment.</param>
    /// <returns>true if the point is contained inside this AABB, false otherwise.</returns>
    bool contains( const glm::vec2& p ) const noexcept
    {
        return glm::all( glm::greaterThanEqual( p, min ) ) && glm::all( glm::lessThanEqual( p, max ) );
    }

    /// <summary>
    /// Returns the closest point to 'p' on or in this AABB.
    /// Note: If 'p' is inside the AABB, 'p' is returned.
    /// </summary>
    /// <param name="p">The point to be clamped to the bounds of the AABB.</param>
    /// <returns>The closest point to 'p' that lies on the bounds of the AABB or 'p' if 'p' is inside the AABB.</returns>
    glm::vec2 closestPoint( const glm::vec2& p ) const noexcept
    {
        return glm::clamp( p, min, max );
    }

    /// <summary>
    /// Calculates the overlap between this axis-aligned bounding box (AABB) and another AABB along the X and Y axes, if they intersect.
    /// </summary>
    /// <param name="aabb">The axis-aligned bounding box to check for overlap with.</param>
    /// <returns>A 2D vector representing the overlap along the X and Y axes if the AABBs intersect; otherwise, an empty optional.</returns>
    std::optional<glm::vec2> overlap( const AABB& aabb ) const noexcept
    {
        glm::vec2 overlap = glm::min( max, aabb.max ) - glm::max( min, aabb.min );

        if ( overlap.x > 0.0f && overlap.y > 0.0f )
        {
            if ( overlap.x < overlap.y )
            {
                return glm::vec2 { ( center().x < aabb.center().x ? max.x - aabb.min.x : min.x - aabb.max.x ), 0.0f };
            }

            return glm::vec2 { 0.0f, ( center().y < aabb.center().y ? max.y - aabb.min.y : min.y - aabb.max.y ) };
        }

        return {};
    }

    /// <summary>
    /// Construct an AABB from min & max points.
    /// </summary>
    /// <param name="min">The min point.</param>
    /// <param name="max">The max point.</param>
    /// <returns></returns>
    static AABB fromMinMax( const glm::vec2& min, const glm::vec2& max )
    {
        return { min, max };
    }

    glm::vec2 min { std::numeric_limits<float>::max() };
    glm::vec2 max { std::numeric_limits<float>::lowest() };
};
}  // namespace math

}  // namespace cpprast
