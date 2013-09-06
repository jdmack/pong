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
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_ = kBallWidth;
    height_ = kBallHeight;

    sprite_ = new Sprite(this, kAssetArtBall);
}

Ball::Ball(Game * game, double x, double y) : GameObject(game, x, y)
{

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
			Logger::write("STOPPING: Collision with LEFT screen boundary");
			stop();
			x_position_ = 0 + (width_ / 2);
		}
		// Check right boundary
		else if(x_position_ + (width_ / 2) > kScreenWidth) {
			Logger::write("STOPPING: Collision with RIGHT screen boundary");
			stop();
			x_position_ = kScreenWidth - (width_ / 2);
		}

		// Check top boundary
		if(y_position_ - (height_ / 2) < 0) {
			Logger::write("STOPPING: Collision with TOP screen boundary");
			stop();
			y_position_ = 0 + (height_ / 2);
		}
		// Check bottom boundary
		else if(y_position_ + (height_ / 2) > kScreenHeight) {
			Logger::write("STOPPING: Collision with BOTTOM screen boundary");
			stop();
			y_position_ = kScreenHeight - (height_ / 2);
		}

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
	/*
    Logger::write("move command");

    current_action_ = new Movement(Vector(x_position_, y_position_, x, y), Coordinate(x, y));

    Movement * movement_command = static_cast<Movement*>(current_action_);
    movement_command->set_distance(Movement::calculate_distance(Coordinate(movement_command->destination().x_position(), movement_command->destination().y_position()), Coordinate(x_position_, y_position_)));

    double dir = movement_command->vector().direction() - rotation_;
    if((dir > 0) && (std::abs(dir) <= 180)) { movement_command->set_clockwise(false); }
    if((dir > 0) && (std::abs(dir) > 180)) { movement_command->set_clockwise(true); }
    if((dir < 0) && (std::abs(dir) <= 180)) { movement_command->set_clockwise(true); }
    if((dir < 0) && (std::abs(dir) > 180)) { movement_command->set_clockwise(false); }

    //dir += (dir > 180) ? -360 : (dir < -180) ? 360 : 0;
    if(dir > 180) {
        dir -= 360;
    }
    else if(dir < -180) {
        dir += 360;
    }
    movement_command->set_degrees(std::abs(dir));

    Vector acceleration(kBallAcceleration, movement_command->vector().direction());

    movement_command->set_maximum_velocity(Vector(kBallVelocity, movement_command->vector().direction()));

    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = acceleration.x_component();
    y_acceleration_ = acceleration.y_component();
    Logger::write(Logger::string_stream << "Move - (x,y): (" << movement_command->destination().x_position() << "," << movement_command->destination().x_position()
            << ") direction: " << movement_command->vector().direction());
*/
}
