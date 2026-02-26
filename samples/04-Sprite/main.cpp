#include "Timer.hpp"

#include <graphics/Rasterizer.hpp>
#include <graphics/ResourceManager.hpp>
#include <graphics/SpriteAnimation.hpp>
#include <graphics/Window.hpp>

constexpr int         SCREEN_WIDTH  = 480;
constexpr int         SCREEN_HEIGHT = 256;
constexpr const char* TITLE         = "04 - Sprite";

using namespace cpprast;

int main()
{
    Window     window( TITLE, SCREEN_WIDTH, SCREEN_HEIGHT );
    Image      image { SCREEN_WIDTH, SCREEN_HEIGHT };
    Rasterizer rasterizer;
    glm::ivec2   mousePos{0};

    rasterizer.state.colorTarget = &image;

    // Load a sprite sheet
    std::shared_ptr<SpriteSheet> spriteSheet = ResourceManager::loadSpriteSheet( "assets/Pixel Adventure/Main Characters/Ninja Frog/Idle (32x32).png", 32, 32, 0, 0, BlendMode::AlphaDiscard );
    // Create a sprite animation.
    SpriteAnimation ninjaFrog_idle { spriteSheet, 12 };

    Timer timer;

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
                switch ( e.key.key )
                {
                case SDLK_ESCAPE:  // Escape key also quits the application
                    window.close();
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
            case SDL_EVENT_MOUSE_MOTION:
                mousePos = window.clientToImage( e.motion.x, e.motion.y, image );
                break;
            }  // switch(e.type)
        }  // while (SDL_PollEvent(&e))

        timer.tick();
        ninjaFrog_idle.update( static_cast<float>( timer.elapsedSeconds() ) );

        image.clear( Color::Black );
        rasterizer.drawSprite( ninjaFrog_idle, mousePos.x - 16, mousePos.y - 16 );

        // Present the image to the screen.
        window.clear( Color::CornflowerBlue );
        window.present( image );

    }  // while(running)

    return 0;
}