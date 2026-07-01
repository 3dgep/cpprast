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

    const AABB       clipAABB = AABB::fromRect( state.clipRect );
    const AABB       dstAABB  = dstImage->getAABB().clamped( clipAABB );
    const glm::ivec2 size     = sprite.getSize();

    // Compute clipping bounds.
    const int clipLeft   = std::max( static_cast<int>( dstAABB.min.x ), _x );
    const int clipTop    = std::max( static_cast<int>( dstAABB.min.y ), _y );
    const int clipRight  = std::min( static_cast<int>( dstAABB.max.x ), _x + size.x - 1 );
    const int clipBottom = std::min( static_cast<int>( dstAABB.max.y ), _y + size.y - 1 );

    // Check if the sprite is completely off-screen.
    if ( clipLeft >= clipRight || clipTop >= clipBottom )
        return;

    // Adjust sprite UV based on clipping.
    glm::ivec2 uv = sprite.getUV();
    uv.x += clipLeft - _x;
    uv.y += clipTop - _y;

    const Color     color     = sprite.getColor();
    const BlendMode blendMode = sprite.getBlendMode();
    int sW = srcImage->getWidth();  // Source image width.
    int dW = dstImage->getWidth();  // Destination image width.

    const Color* src = srcImage->data();
    Color*       dst = dstImage->data();

    for ( int y = clipTop; y <= clipBottom; ++y )
    {
        int v = uv.y + ( y - clipTop );
        for ( int x = clipLeft; x <= clipRight; ++x )
        {
            // Compute clipped UV sprite texture coordinates.
            int u = uv.x + ( x - clipLeft );

            Color sC = src[v * sW + u] * color;
            Color dC = dst[y * dW + x];

            dst[y * dW + x] = blendMode.Blend( sC, dC );
        }
    }
}