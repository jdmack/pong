#ifndef PONG_GAME_OBJECT_H_
#define PONG_GAME_OBJECT_H_

#include "SDL/SDL.h"
#include "assets.h"
#include "vector.h"

class Action;
class Sprite;
class Game;

class GameObject
{
    protected:
        double x_position_;
        double y_position_;
        double x_velocity_;
        double y_velocity_;
        double x_acceleration_;
        double y_acceleration_;
        double width_;
        double height_;

        Game * game_;
        Sprite * sprite_;

    public:
        // constructors/destructors
        GameObject(Game * game);
        GameObject(Game * game, double x, double y);
        virtual ~GameObject();

        // accessors
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double x_velocity() const { return x_velocity_; }
        double y_velocity() const { return y_velocity_; }
        double x_acceleration() const { return x_acceleration_; }
        double y_acceleration() const { return y_acceleration_; }
        double width() const { return width_; }
        double height() const { return height_; }
        Sprite * sprite() const { return sprite_; }
        SDL_Rect rect();

        virtual bool contains_point(double x, double y);
        virtual void move(double x, double y);
        virtual void stop();
        void render();
        void set_sprite(Sprite * sprite) { sprite_ = sprite; }
        bool stopped();

        bool check_collision(SDL_Rect rect);
        void fix_collision(SDL_Rect rect);

};

#endif
