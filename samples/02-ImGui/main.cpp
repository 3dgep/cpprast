#include <graphics/Window.hpp>

#include <imgui.h>

constexpr int         SCREEN_WIDTH  = 800;
constexpr int         SCREEN_HEIGHT = 600;
constexpr const char* TITLE         = "02 - ImGui";

using namespace cpprast;

int main()
{
    Window window( TITLE, SCREEN_WIDTH, SCREEN_HEIGHT );

    while ( window )
    {
        SDL_Event e;
        while ( SDL_PollEvent( &e ) )  // Poll for any new events on the event queue.
        {
            switch ( e.type )
            {
            case SDL_EVENT_QUIT:  // Closing the window quits the application
                window.destroy();
                break;
            case SDL_EVENT_KEY_DOWN:
                switch ( e.key.key )
                {
                case SDLK_ESCAPE:  // Escape key also quits the application
                    window.destroy();
                    break;
                case SDLK_V:
                    window.toggleVSync();
                    break;
                case SDLK_RETURN:
                    if ( ( e.key.mod & SDL_KMOD_ALT ) != 0 )
                    {
                    case SDLK_F11:  // NOLINT(clang-diagnostic-implicit-fallthrough)
                        window.toggleFullscreen();
                    }
                    break;
                }  // switch (e.key.key)
                break;  // SDL_EVENT_KEY_DOWN
            }  // switch(e.type)
        }  // while (SDL_PollEvent(&e))

        ImGui::ShowDemoWindow();

        // Clear the screen.
        window.clear( 154, 206, 235 );
        window.present();
    }  // while(running)

    return 0;
}