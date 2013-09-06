/* Event Agent */

#include <vector>
#include "SDL/SDL.h"
#include "evengent.h"
#include "game.h"
#include "game_object.h"
#include "util/logger.h"
#include "ball.h"

Evengent::Evengent()
{
    game_ = nullptr;
}

void Evengent::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {

        // timer checks
        if((focus_timer_.started()) && (focus_timer_.get_ticks() >= kFocusTimeout)) {
            game_->set_quit(true);
            Logger::write("Setting game quit");
        }

        // Handle Events
        switch(event.type) {
            case SDL_QUIT:  // Quit Event (user x's the window)
                game_->set_quit(true);
                break;

            case SDL_KEYDOWN:   // Keypress
                switch(event.key.keysym.sym) {

                    case SDLK_ESCAPE:   // Escape
                        game_->set_quit(true);
                        break;
                    case SDLK_UP:       // Up Arrow
                        break;
                    case SDLK_DOWN:     // Down Arrow
                        break;
                    case SDLK_LEFT:     // Left Arrow
                        break;
                    case SDLK_RIGHT:    // Right Arrow
                        break;
                }
                break;

            case SDL_KEYUP:
                switch( event.key.keysym.sym) {
                    case SDLK_UP:       // Up Arrow
                        break;
                    case SDLK_DOWN:    // Down Arrow
                        break;
                    case SDLK_LEFT:    // Left Arrow
                        break;
                    case SDLK_RIGHT:    // Right Arrow
                        break;
                }
                break;

            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    focus_timer_.start();
                    Logger::write("focus_timer started");
                }
                if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    if(focus_timer_.started()) {
                        focus_timer_.stop();
                        Logger::write("focus_timer stopped");
                    }
                }
                break;
        }
    }
}
