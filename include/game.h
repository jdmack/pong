#ifndef PONG_PONG_GAME_H_
#define PONG_PONG_GAME_H_

#include "SDL/SDL.h"
#include "timer.h"

class Evengent;
class Entigent;
class Screen;

class Game
{
    private:
        int exit_code_;
        bool quit_;
        Timer delta_timer_;
        Screen * screen_;
        Evengent * evengent_;
        Entigent * entigent_;

    public:
        Game();
        ~Game();
        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);

        // accessors
        Screen * screen() const { return screen_; }
        Evengent * evengent() const { return evengent_; }
        Entigent * entigent() const { return entigent_; }

        // mutators
        void set_quit(bool quit) { quit_ = quit; }
};

#endif
