#pragma once

#include "Sprite.hpp"

#include <math/Line.hpp>
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
        Image*    colorTarget = nullptr;                    ///< The image to draw to.
        Color     color       = Color::White;               ///< Blend color.
        BlendMode blendMode;                                ///< The blend mode to use when drawing.
        RectUI    clipRect { 0u, 0u, UINT_MAX, UINT_MAX };  ///< The clipping rectangle that restricts drawing to a specific region of the color target.
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

    /// <summary>
    /// Draws a line from (x0, y0) to (x1, y1) using the current rasterizer state.<br>
    /// Required state:
    /// - color
    /// - blendMode
    /// - colorTarget
    /// - clipRect
    /// </summary>
    /// <param name="x0">The x-coordinate of the starting point.</param>
    /// <param name="y0">The y-coordinate of the starting point.</param>
    /// <param name="x1">The x-coordinate of the ending point.</param>
    /// <param name="y1">The y-coordinate of the ending point.</param>
    void drawLine( int x0, int y0, int x1, int y1 ) const;

    /// <summary>
    /// Draws a line from (x0, y0) to (x1, y1) using the current rasterizer state.<br>
    /// Required state:
    /// - color
    /// - blendMode
    /// - colorTarget
    /// - clipRect
    /// </summary>
    /// <param name="x0">The x-coordinate of the starting point.</param>
    /// <param name="y0">The y-coordinate of the starting point.</param>
    /// <param name="x1">The x-coordinate of the ending point.</param>
    /// <param name="y1">The y-coordinate of the ending point.</param>
    void drawLine( float x0, float y0, float x1, float y1 ) const
    {
        drawLine( static_cast<int>( x0 ), static_cast<int>( y0 ), static_cast<int>( x1 ), static_cast<int>( y1 ) );
    }

    /// <summary>
    /// Draws a line from p0 to p1 using the current rasterizer state.<br>
    /// Required state:
    /// - color
    /// - blendMode
    /// - colorTarget
    /// - clipRect
    /// </summary>
    /// <param name="p0">The starting point of the line.</param>
    /// <param name="p1">The endpoint of the line.</param>
    void drawLine( const glm::vec2& p0, const glm::vec2& p1 ) const
    {
        drawLine( p0.x, p0.y, p1.x, p1.y );
    }

    /// <summary>
    /// Draws a line from p0 to p1 using the current rasterizer state.<br>
    /// Required state:
    /// - color
    /// - blendMode
    /// - colorTarget
    /// - clipRect
    /// </summary>
    /// <param name="p0">The starting point of the line.</param>
    /// <param name="p1">The endpoint of the line.</param>
    void drawLine( const glm::ivec2& p0, const glm::ivec2& p1 ) const
    {
        drawLine( p0.x, p0.y, p1.x, p1.y );
    }

    /// <summary>
    /// Draws a line using the current rasterizer state.<br>
    /// Required state:
    /// - color
    /// - blendMode
    /// - colorTarget
    /// - clipRect
    /// </summary>
    /// <param name="line">The line to draw.</param>
    void drawLine( const math::Line& line ) const
    {
        drawLine( line.p0.x, line.p0.y, line.p1.x, line.p1.y );
    }

private:
    /// <summary>
    /// Draws a line between two points using an algorithm optimized for lines with a shallow slope (|dy| < |dx|).
    /// </summary>
    /// <param name="x0">The x-coordinate of the starting point.</param>
    /// <param name="y0">The y-coordinate of the starting point.</param>
    /// <param name="x1">The x-coordinate of the ending point.</param>
    /// <param name="y1">The y-coordinate of the ending point.</param>
    void drawLineLow( int x0, int y0, int x1, int y1 ) const;

    /// <summary>
    /// Draws a line between two points using an algorithm optimized for lines with a steep slope (|dy| > |dx|).
    /// </summary>
    /// <param name="x0">The x-coordinate of the starting point.</param>
    /// <param name="y0">The y-coordinate of the starting point.</param>
    /// <param name="x1">The x-coordinate of the ending point.</param>
    /// <param name="y1">The y-coordinate of the ending point.</param>
    void drawLineHigh( int x0, int y0, int x1, int y1 ) const;
};

}  // namespace graphics
}  // namespace cpprast