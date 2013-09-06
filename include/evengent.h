/* Event Agent */

#ifndef PONG_EVENGENT_H_
#define PONG_EVENGENT_H_

#include "timer.h"

class Game;

const double kFocusTimeout = 10000;

class Evengent
{
    private:
        Game * game_;
        Timer focus_timer_;

    public:
        Evengent();
        void handle_events();

        // mutators
        void set_game(Game * game) { game_ = game; }
};

#endif
