#include <graphics/Rasterizer.hpp>

using namespace cpprast::graphics;
using namespace cpprast::math;

void Rasterizer::clear( const Color& color )
{
    if ( Image* image = state.colorTarget )
        image->clear( color );
}

void Rasterizer::drawSprite( const Sprite& sprite, int _x, int _y )
{
    const Image* srcImage = sprite.getImage().get();
    Image*       dstImage = state.colorTarget;

    if ( !srcImage || !dstImage )
        return;

    const Color      color     = sprite.getColor();
    const BlendMode  blendMode = sprite.getBlendMode();
    const AABB       clipAABB  = AABB::fromRect( state.clipRect );
    const AABB       dstAABB   = dstImage->getAABB().clamped( clipAABB );
    const glm::ivec2 size      = sprite.getSize();
    glm::ivec2       uv        = sprite.getUV();

    // Compute viewport clipping bounds.
    const int clipLeft   = std::max( static_cast<int>( dstAABB.min.x ), _x );
    const int clipTop    = std::max( static_cast<int>( dstAABB.min.y ), _y );
    const int clipRight  = std::min( static_cast<int>( dstAABB.max.x ), _x + size.x - 1 );
    const int clipBottom = std::min( static_cast<int>( dstAABB.max.y ), _y + size.y - 1 );

    // Check if the sprite is completely off-screen.
    if ( clipLeft >= clipRight || clipTop >= clipBottom )
        return;

    // Adjust sprite UV based on clipping.
    uv.x += clipLeft - _x;
    uv.y += clipTop - _y;

    const Color* src = srcImage->data();
    Color*       dst = dstImage->data();

    int sW = srcImage->getWidth();  // Source image width.
    int dW = dstImage->getWidth();  // Destination image width.

    for ( int y = clipTop; y <= clipBottom; ++y )
    {
        for ( int x = clipLeft; x <= clipRight; ++x )
        {
            // Compute clipped UV sprite texture coordinates.
            int u = uv.x + ( x - clipLeft );
            int v = uv.y + ( y - clipTop );

            Color sC = src[v * sW + u] * color;
            Color dC = dst[y * dW + x];

            dst[y * dW + x] = blendMode.Blend( sC, dC );
        }
    }
}

// Source: Claud Sonnet 4 "Create a 2D Software Rasterizer in C++"
void Rasterizer::drawLineLow( int x0, int y0, int x1, int y1 ) const
{
    Image*    image     = state.colorTarget;
    BlendMode blendMode = state.blendMode;

    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;

    if ( dy < 0 )
    {
        yi = -1;
        dy = -dy;
    }

    int D = 2 * dy - dx;
    int y = y0;

    for ( int x = x0; x <= x1; ++x )
    {
        image->plot<false>( x, y, state.color, blendMode );

        if ( D > 0 )
        {
            y += yi;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void Rasterizer::drawLineHigh( int x0, int y0, int x1, int y1 ) const
{
    Image*    image     = state.colorTarget;
    BlendMode blendMode = state.blendMode;

    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;

    if ( dx < 0 )
    {
        xi = -1;
        dx = -dx;
    }

    int D = 2 * dx - dy;
    int x = x0;

    for ( int y = y0; y <= y1; ++y )
    {
        image->plot<false>( x, y, state.color, blendMode );

        if ( D > 0 )
        {
            x += xi;
            D -= 2 * dy;
        }

        D += 2 * dx;
    }
}

void Rasterizer::drawLine( int x0, int y0, int x1, int y1 ) const
{
    Image* image = state.colorTarget;

    if ( !image )
        return;

    auto aabb = image->getAABB();
    aabb.clamp( AABB::fromRect( state.clipRect ) );

    if ( !aabb.clip( x0, y0, x1, y1 ) )
        return;

    if ( std::abs( y1 - y0 ) < std::abs( x1 - x0 ) )
    {
        if ( x0 > x1 )
        {
            drawLineLow( x1, y1, x0, y0 );
        }
        else
        {
            drawLineLow( x0, y0, x1, y1 );
        }
    }
    else
    {
        if ( y0 > y1 )
        {
            drawLineHigh( x1, y1, x0, y0 );
        }
        else
        {
            drawLineHigh( x0, y0, x1, y1 );
        }
    }
}
