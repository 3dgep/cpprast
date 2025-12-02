#pragma once

#include <limits>

namespace cpprast
{
inline namespace math
{
struct Viewport
{
    explicit Viewport( float x = 0.0f, float y = 0.0f, float width = std::numeric_limits<float>::max(), float height = std::numeric_limits<float>::max(), float minDepth = 0.0f, float maxDepth = 1.0f )
    : x { x }
    , y { y }
    , width { width }
    , height { height }
    , minDepth { minDepth }
    , maxDepth { maxDepth }
    {}

    float x        = 0.0f;                               ///< X-position of the left side of the viewport.
    float y        = 0.0f;                               ///< Y-position of the top of the viewport.
    float width    = std::numeric_limits<float>::max();  ///< Width of the viewport in pixels.
    float height   = std::numeric_limits<float>::max();  ///< Height of the viewport in pixels.
    float minDepth = 0.0f;                               ///< Minimum depth of the viewport in the range (0...1).
    float maxDepth = 1.0f;                               // Maximum depth of the viewport in the range (0...1).
};
}  // namespace math
}  // namespace cpprast
