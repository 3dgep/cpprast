#pragma once  // Always at the top of header files.

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <string_view>

// Forward declaration to avoid including imgui headers in this file.
struct ImGuiContext;

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
    void destroy();

    void close();

    void clear( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255 );
    void present();

    void resize( int width, int height );

    void setFullscreen( bool fullscreen );

    void toggleFullscreen();

    bool isFullscreen() const noexcept;

    void setVSync( bool enabled );

    void toggleVSync();

    bool isVSync() const noexcept;

    // Set this window as the current ImGui context.
    bool setCurrent();

private:
    static bool SDLCALL eventWatch( void* userdata, SDL_Event* event );

    // Begin a new ImGui frame.
    void beginFrame();

    SDL_Window*   m_Window   = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    ImGuiContext* m_ImGuiContext = nullptr;

    int  m_Width      = -1;
    int  m_Height     = -1;
    bool m_Fullscreen = false;
    bool m_VSync      = true;
    bool m_Close      = false;
};

}  // namespace graphics
}  // namespace cpprast
