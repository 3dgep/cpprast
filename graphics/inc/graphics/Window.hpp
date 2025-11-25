#pragma once // Always at the top of header files.

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <string_view>

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

    void create( std::string_view title, int width, int height, bool fullScreen = false );
    void destroy();

    bool pollEvent( SDL_Event& event );

    void clear( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255 );
    void present();

    void resize( int width, int height );

    void setFullscreen( bool fullscreen );

    void toggleFullscreen();

    bool isFullscreen() const noexcept;

    void setVSync( bool enabled );

    void toggleVSync();

    bool isVSync() const noexcept;

private:
    SDL_Window*   m_Window   = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    int  m_Width      = -1;
    int  m_Height     = -1;
    bool m_Fullscreen = false;
    bool m_VSync      = true;
};

}  // namespace graphics
}  // namespace cpprast
