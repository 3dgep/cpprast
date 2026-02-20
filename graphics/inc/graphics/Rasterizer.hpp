#pragma once

#include "Sprite.hpp"
#include <math/Rect.hpp>

namespace cpprast
{
inline namespace graphics
{
class Rasterizer
{
public:
    /// <summary>
    /// Don't forget to configure the state of the rasterizer before calling any draw functions!
    /// </summary>
    struct State
    {
        Image* colorTarget = nullptr;                    ///< The image to draw to.
        RectUI clipRect { 0u, 0u, UINT_MAX, UINT_MAX };  ///< The clipping rectangle that restricts drawing to a specific region of the color target.
    } state;

    /// <summary>
    /// Clear the color target.
    /// </summary>
    /// <param name="color">The color to clear the color target to. Default: Black.</param>
    void clear( const Color& color = Color::Black );

    /// <summary>
    /// Draw a sprite to the color target at the specified screen position.
    /// The sprite is clipped to the viewport and destination image bounds.
    /// The sprite's color, blend mode, and UV region are applied during rendering.
    /// </summary>
    /// <param name="sprite">The sprite to draw.</param>
    /// <param name="x">The x-coordinate of the top-left corner of the sprite on the color target.</param>
    /// <param name="y">The y-coordinate of the top-left corner of the sprite on the color target.</param>
    void drawSprite( const Sprite& sprite, int x, int y );
};

}  // namespace graphics
}  // namespace cpprast