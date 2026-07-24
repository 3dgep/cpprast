#include "glm/gtc/random.hpp"

#include <graphics/Image.hpp>
#include <graphics/Rasterizer.hpp>
#include <graphics/Window.hpp>

constexpr int         SCREEN_WIDTH  = 800;
constexpr int         SCREEN_HEIGHT = 600;
constexpr const char* TITLE         = "05 - Lines";

using namespace cpprast;

int main()
{
    Window     window( TITLE, SCREEN_WIDTH, SCREEN_HEIGHT );
    Image      image( SCREEN_WIDTH, SCREEN_HEIGHT );
    Rasterizer rasterizer;
    rasterizer.state.colorTarget = &image;

    while ( window )
    {
        SDL_Event e;
        while ( SDL_PollEvent( &e ) )  // Poll for any new events on the event queue.
        {
            switch ( e.type )
            {
            case SDL_EVENT_QUIT:  // Closing the window quits the application
                window.close();
                break;
            case SDL_EVENT_KEY_DOWN:
                switch ( e.key.scancode )
                {
                case SDL_SCANCODE_ESCAPE:  // Escape key also quits the application
                    window.close();
                    break;
                case SDL_SCANCODE_V:
                    window.toggleVSync();
                    break;
                case SDL_SCANCODE_RETURN:
                    if ( ( e.key.mod & SDL_KMOD_ALT ) != 0 )
                    {
                    case SDL_SCANCODE_F11:  // NOLINT(clang-diagnostic-implicit-fallthrough)
                        window.toggleFullscreen();
                    }
                    break;
                case SDL_SCANCODE_C:
                case SDL_SCANCODE_R:
                    image.clear( Color::Black );
                    break;
                }  // switch (e.key.scancode)
                break;  // SDL_EVENT_KEY_DOWN
            }  // switch(e.type)
        }  // while (SDL_PollEvent(&e))

        // Draw a random line on the screen.
        glm::vec2 p0 = glm::linearRand( glm::vec2( -SCREEN_WIDTH, -SCREEN_HEIGHT ), glm::vec2( 2 * SCREEN_WIDTH, 2 * SCREEN_HEIGHT ) );
        glm::vec2 p1 = glm::linearRand( glm::vec2( -SCREEN_WIDTH, -SCREEN_HEIGHT ), glm::vec2( 2 * SCREEN_WIDTH, 2 * SCREEN_HEIGHT ) );
        // Set a random color to draw the line.
        rasterizer.state.color = Color::fromHSV( glm::linearRand( 0.0f, 360.0f ) );

        rasterizer.drawLine( p0, p1 );

        window.clear( Color::Black );
        window.present( image );

    }  // while(running)

    return 0;
}