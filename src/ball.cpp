#include <cmath>
#include "SDL/SDL.h"
#include "ball.h"
#include "assets.h"
#include "util/logger.h"
#include "screen.h"
#include "vector.h"
#include "sprite.h"
#include "game.h"

Ball::Ball(Game * game) : GameObject(game)
{
    width_ = kBallWidth;
    height_ = kBallWidth;
    sprite_ = new Sprite(this, kAssetArtBall);
}

Ball::Ball(Game * game, double x, double y) : GameObject(game, x, y)
{
    width_ = kBallWidth;
    height_ = kBallWidth;
    sprite_ = new Sprite(this, kAssetArtBall);
}

void Ball::update(int delta_ticks)
{
    if((x_velocity_ == 0) && (y_velocity_ == 0)) {
        if((x_acceleration_ == 0) && (y_acceleration_ == 0)) {
            return;
        }
    }

    // Accelerate
    /*
    if((std::abs(x_velocity_) < std::abs(movement_command->maximum_velocity().x_component())) || ( std::abs(y_velocity_) < std::abs(movement_command->maximum_velocity().y_component())) ) {
        x_velocity_ += x_acceleration_ * (delta_ticks / 1000.f);
        y_velocity_ += y_acceleration_ * (delta_ticks / 1000.f);
    }
    */

    // Move left/right
    x_position_ += x_velocity_ * (delta_ticks / 1000.f);

    // Move up/down
    y_position_ += y_velocity_ * (delta_ticks / 1000.f);

    // Check collisions
    // Check left boundary
    if(x_position_ - (width_ / 2) < 0) {
        Logger::write("Collision with LEFT screen boundary");
        // Goal right side
        x_position_ = 0 + (width_ / 2);
        x_velocity_ *= -1;
    }
    // Check right boundary
    else if(x_position_ + (width_ / 2) > kScreenWidth) {
        Logger::write("Collision with RIGHT screen boundary");
        // Goal right side
        x_position_ = kScreenWidth - (width_ / 2);
        x_velocity_ *= -1;
    }

    // Check top boundary
    if(y_position_ - (height_ / 2) < 0) {
        Logger::write("Collision with TOP screen boundary");
        // Bounce
        y_position_ = 0 + (height_ / 2);
        y_velocity_ *= -1;
    }
    // Check bottom boundary
    else if(y_position_ + (height_ / 2) > kScreenHeight) {
        Logger::write("Collision with BOTTOM screen boundary");
        // Bounce
        y_position_ = kScreenHeight - (height_ / 2);
        y_velocity_ *= -1;
    }

    // Check Paddle collisions

}

bool Ball::contains_point(double x, double y)
{
    //if((x < x_position_) || (x > x_position_ + width_)) {
    if((x < (x_position_ - (width_ / 2))) || (x > (x_position_ + (width_ / 2)))) {
        return false;
    }
    //else if((y < y_position_) || (y > y_position_ + height_)) {
    else if((y < (y_position_ - (width_ / 2))) || (y > (y_position_ + (height_ / 2)))) {
        return false;
    }

    return true;
}

void Ball::move(double x, double y)
{
    x_position_ = x;
    y_position_ = y;
}

void Ball::reset()
{
    x_position_ = kScreenWidth / 2;
    y_position_ = kScreenHeight / 2;
}

void Ball::serve(int direction)
{
    // Pick random point on serve line

    // Pick random angle between point->top corner and point->bottom corner

    // Set x/y velocity for that vector
}
