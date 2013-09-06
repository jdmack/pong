#include "game_object.h"
#include "screen.h"
#include "util/logger.h"
#include "vector.h"
#include "sprite.h"
#include "game.h"

GameObject::GameObject(Game * game)
{
    x_position_ = 0;
    y_position_ = 0;
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
    width_ = 0;
    height_ = 0;

    game_ = game;
    sprite_ = nullptr;
}

GameObject::GameObject(Game * game, double x, double y)
{
    x_position_ = x;
    y_position_ = y;
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
    width_ = 0;
    height_ = 0;

    game_ = game;
    sprite_ = nullptr;
}

GameObject::~GameObject()
{

}

void GameObject::render()
{
    sprite_->render();
}

bool GameObject::contains_point(double x, double y)
{
    Logger::write("GameObject::contains_point");
    return true;
}

void GameObject::move(double x, double y)
{
    // TODO(2013-08-27/JM): Handle rotating

}

void GameObject::stop()
{
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
}

SDL_Rect GameObject::rect()
{
    SDL_Rect rect = { (int)x_position_, (int)y_position_, (int)width_, (int)height_ };
    return rect;
}

bool GameObject::check_collision(SDL_Rect rect)
{
    double this_top = y_position_ - (height_ / 2);
    double this_bottom = y_position_ + (height_ / 2);
    double this_left = x_position_ - (width_ / 2);
    double this_right = x_position_ + (width_ / 2);

    double other_top = rect.y;
    double other_bottom = rect.y + rect.h;
    double other_left = rect.x;
    double other_right = rect.x + rect.w;


    if(this_top >= other_bottom) {
        return false;
    }

    if(this_bottom <= other_top) {
        return false;
    }


    if(this_left >= other_right) {
        return false;
    }

    if(this_right <= other_left) {
        return false;
    }

    return true;
}
// TODO(2013-09-05/JM): Create a colission class to add to all objects to use for top/bottom/left/right/etc boundaries instead of always doing this x + (w/2) stuff
void GameObject::fix_collision(SDL_Rect rect)
{
    //if(x_velocity_ >
// TODO(2013-09-05/JM): Finish this function



}

bool GameObject::stopped()
{
    if((x_velocity_ == 0) && (y_velocity_ == 0) && (x_acceleration_ == 0) && (y_acceleration_ == 0)) {
        return true;
    }
    return false;
}

