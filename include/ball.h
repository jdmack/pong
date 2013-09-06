#ifndef PONG_BALL_H_
#define PONG_BALL_H_

#include "game_object.h"

const int kBallWidth  = 40;
const int kBallHeight = 40;

const double kBallVelocity     = 400;
const double kBallAcceleration = 800;
const double kBallRotationVelocity = 200;

class Game;

class Ball : public GameObject
{
    private:

    public:
        // constructors/destructors
        Ball(Game * game);
        Ball(Game * game, double x, double y);

        // overridden
        void select();
        void deselect();
        bool contains_point(double x, double y);
        void move(double x, double y);

        void update(int deltaTicks);

        // accessors
};

#endif
