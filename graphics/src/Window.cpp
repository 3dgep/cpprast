#include <graphics/Window.hpp>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <mutex>

#include <stdexcept>
#include <utility>  // for std::exchange

using namespace cpprast;

struct SDL_Context
{
    static SDL_Context& get()
    {
        static SDL_Context instance;
        return instance;
    }

private:
    SDL_Context()
    {
        if ( !SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMEPAD ) )
        {
            SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError() );
            throw std::runtime_error( SDL_GetError() );
        }
    }

    ~SDL_Context()
    {
        SDL_Quit();
    }
};

struct ImGui_Context
{
    static ImGui_Context& get()
    {
        static ImGui_Context instance;
        return instance;
    }

private:
    // ReSharper disable once CppParameterMayBeConstPtrOrRef
    static bool SDLCALL eventWatch( void* /*userdata*/, SDL_Event* event )
    {
        ImGui_ImplSDL3_ProcessEvent( event );
        return true;
    }

    ImGui_Context()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable multiple window/viewports. NOTE: SDL3 backend does not currently support Multi-viewports.

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsLight();

        // Setup initial scaling
        float primaryDisplayScale = SDL_GetDisplayContentScale( SDL_GetPrimaryDisplay() );

        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes( primaryDisplayScale );        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi         = primaryDisplayScale;  // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
        io.ConfigDpiScaleViewports = true;                 // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.

        SDL_AddEventWatch( &eventWatch, this );
    }

    ~ImGui_Context()
    {
        // Cleanup
        SDL_RemoveEventWatch( &eventWatch, this );
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    // Make sure the event watcher is only added once.
    std::once_flag m_OnceFlag;
};

Window::~Window()
{
    destroy();
}

Window::Window( std::string_view title, int width, int height, bool fullscreen )
{
    create( title, width, height, fullscreen );
}

Window::Window( Window&& window ) noexcept
: m_Window( std::exchange( window.m_Window, nullptr ) )
, m_Renderer( std::exchange( window.m_Renderer, nullptr ) )
, m_Width( std::exchange( window.m_Width, -1 ) )
, m_Height( std::exchange( window.m_Height, -1 ) )
, m_Fullscreen( std::exchange( window.m_Fullscreen, false ) )
, m_VSync( std::exchange( window.m_VSync, true ) )
{}

Window& Window::operator=( Window&& window ) noexcept
{
    if ( this == &window )
        return *this;

    m_Window     = std::exchange( window.m_Window, nullptr );
    m_Renderer   = std::exchange( window.m_Renderer, nullptr );
    m_Width      = std::exchange( window.m_Width, -1 );
    m_Height     = std::exchange( window.m_Height, -1 );
    m_Fullscreen = std::exchange( window.m_Fullscreen, false );
    m_VSync      = std::exchange( window.m_VSync, true );

    return *this;
}

bool Window::isValid() const
{
    return m_Window != nullptr && !m_Close;
}

Window::operator bool() const
{
    return isValid();
}

void Window::create( std::string_view title, int width, int height, bool fullScreen )
{
    static SDL_Context& SDL_context = SDL_Context::get();  // Ensure a single, static context before creating an SDL window.

    if ( m_Window )
        destroy();  // Destroy existing window if any.

    m_Fullscreen          = fullScreen;
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
    flags |= m_Fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if ( !SDL_CreateWindowAndRenderer( title.data(), width, height, flags, &m_Window, &m_Renderer ) )  // NOLINT(bugprone-suspicious-stringview-data-usage)
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to create window and renderer: %s", SDL_GetError() );
        throw std::runtime_error( SDL_GetError() );
    }

    if ( !SDL_AddEventWatch( &Window::eventWatch, this ) )
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to add event watch: %s", SDL_GetError() );
        throw std::runtime_error( SDL_GetError() );
    }

    // Enable vsync.
    SDL_SetRenderVSync( m_Renderer, m_VSync ? 1 : 0 );

    resize( width, height );

    // The imgui context must be created after the Window and renderer have been created.
    static ImGui_Context& ImGui_context = ImGui_Context::get();  // Ensure a single, static ImGui context before creating an SDL window.

    // Setup Platform/Renderer backends for ImGui.
    ImGui_ImplSDL3_InitForSDLRenderer( m_Window, m_Renderer );
    ImGui_ImplSDLRenderer3_Init( m_Renderer );

    beginFrame();
}

void Window::resize( int width, int height )
{
    if ( m_Width != width || m_Height != height )
    {
        width  = std::max( 1, width );   // Avoid zero or negative dimensions.
        height = std::max( 1, height );  // Avoid zero or negative dimensions.

        if ( !SDL_SetWindowSize( m_Window, width, height ) )
        {
            SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to resize window: %s", SDL_GetError() );
            return;
        }

        m_Width  = width;
        m_Height = height;
    }
}

void Window::setFullscreen( bool fullscreen )
{
    if ( m_Window )
    {
        SDL_SetWindowFullscreen( m_Window, fullscreen );
        m_Fullscreen = fullscreen;
    }
}

void Window::toggleFullscreen()
{
    setFullscreen( !m_Fullscreen );
}

bool Window::isFullscreen() const noexcept
{
    return m_Fullscreen;
}

void Window::setVSync( bool enabled )
{
    if ( m_Renderer )
    {
        SDL_SetRenderVSync( m_Renderer, enabled ? 1 : 0 );
        m_VSync = enabled;
    }
}

void Window::toggleVSync()
{
    setVSync( !m_VSync );
}

bool Window::isVSync() const noexcept
{
    return m_VSync;
}

void Window::destroy()
{
    SDL_RemoveEventWatch( &Window::eventWatch, this );

    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );

    m_Window   = nullptr;
    m_Renderer = nullptr;
    m_Width    = -1;
    m_Height   = -1;
}

void Window::clear( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha )
{
    if ( !m_Renderer )
        return;

    SDL_SetRenderDrawColor( m_Renderer, red, green, blue, alpha );
    SDL_RenderClear( m_Renderer );
}

void Window::present()
{
    if ( !m_Renderer )
        return;

    // ImGui rendering
    ImGui::Render();

    // Update for multiple viewports
    // Note: Multi-viewports are not yet supported with the SDL3 backend.
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();

    ImGui_ImplSDLRenderer3_RenderDrawData( ImGui::GetDrawData(), m_Renderer );

    if ( !SDL_RenderPresent( m_Renderer ) )
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to present: %s", SDL_GetError() );
    }

    if ( m_Close )
        destroy();
    else
        beginFrame();
}

bool SDLCALL Window::eventWatch( void* userdata, SDL_Event* event )
{
    Window* self = static_cast<Window*>( userdata );

    switch ( event->type )
    {
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        if ( event->window.windowID == SDL_GetWindowID( self->m_Window ) )
        {
            self->m_Close = true;  // Mark the window to be closed.
            // Note: Destroying the window here will cause a crash later in the event processing.
            // The actual destruction is deferred to present function.
        }
        break;
    case SDL_EVENT_WINDOW_RESIZED:
        if ( event->window.windowID == SDL_GetWindowID( self->m_Window ) )
        {
            self->m_Width  = event->window.data1;
            self->m_Height = event->window.data2;
        }
        break;
    }

    return true;
}

void Window::beginFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}
