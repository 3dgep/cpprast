#pragma once  // Always at the top of header files.

#include "Image.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include <string_view>

// Forward declaration to avoid including headers in this file.
struct ImGuiContext;
struct SDL_Window;
struct SDL_Renderer;

namespace cpprast
{
inline namespace graphics
{
class Window
{
public:
    Window() = default;
    ~Window();

    Window( std::string_view title, int width, int height, bool fullscreen = false );
    Window( const Window& ) = delete;  // Delete copy constructor
    Window( Window&& window ) noexcept;

    Window& operator=( const Window& ) = delete;  // Delete copy assignment
    Window& operator=( Window&& window ) noexcept;

    explicit operator bool() const;  // Allow conversion to bool.

    bool isValid() const;

    void create( std::string_view title, int width, int height, bool fullScreen = false );
    void destroy() noexcept;

    void close();

    void clear( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255 );

    void clear( const Color& color )
    {
        clear( color.channels.r, color.channels.g, color.channels.b, color.channels.a );
    }

    void present();

    void present( const Image& image );

    void resize( int width, int height );

    void setFullscreen( bool fullscreen );

    void toggleFullscreen();

    bool isFullscreen() const noexcept;

    void setVSync( bool enabled );

    void toggleVSync();

    bool isVSync() const noexcept;

    // Set this window as the current ImGui context.
    bool setCurrent();

    /// <summary>
    /// Convert coordinates from window client space to image space.
    /// </summary>
    /// <param name="x">The x-coordinate in window client space.</param>
    /// <param name="y">The y-coordinate in window client space.</param>
    /// <param name="image">The target image to convert coordinates for.</param>
    /// <returns>The converted coordinates in image space.</returns>
    glm::vec2 clientToImage( float x, float y, const Image& image ) const noexcept;

    /// <summary>
    /// Convert coordinates from window client space to image space.
    /// </summary>
    /// <param name="clientCoords">The coordinates in window client space.</param>
    /// <param name="image">The target image to convert coordinates for.</param>
    /// <returns>The converted coordinates in image space.</returns>
    glm::vec2 clientToImage( const glm::vec2& clientCoords, const Image& image ) const noexcept
    {
        return clientToImage( clientCoords.x, clientCoords.y, image );
    }

private:
    static bool SDLCALL eventWatch( void* userdata, SDL_Event* event );

    // Begin a new ImGui frame.
    void beginFrame();

    SDL_Window*   m_Window       = nullptr;
    SDL_Renderer* m_Renderer     = nullptr;
    SDL_Texture*  m_Texture      = nullptr;
    ImGuiContext* m_ImGuiContext = nullptr;

    int  m_Width      = -1;
    int  m_Height     = -1;
    bool m_Fullscreen = false;
    bool m_VSync      = true;
    bool m_Close      = false;
};

}  // namespace graphics
}  // namespace cpprast
