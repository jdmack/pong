#include "SDL/SDL.h"

// Project Files
#include "game.h"
#include "ball.h"
#include "assets.h"
#include "screen.h"
#include "evengent.h"
#include "entigent.h"
#include "util/logger.h"


Game::Game()
{
    exit_code_ = 0;
    quit_ = false;
    screen_ = new Screen();
    evengent_ = new Evengent();
    evengent_->set_game(this); // TODO
    entigent_ = new Entigent();
    entigent_->set_game(this); // TODO
}

Game::~Game()
{
    delete screen_;
}

int Game::run()
{
    Logger::open(kLogFilename);
    Logger::write("running");

    if(screen_->init() == false) {
        return 1;
    }

    delta_timer_.start();

    game_loop();

    //Clean up
    screen_->clean_up();

    Logger::write("shutting down");
    return exit_code_;
}

void Game::game_loop()
{
	// Create ball and two paddles
    Ball * ball = new Ball(this, kScreenWidth / 2, kScreenHeight / 2);
    //Paddle * left_paddle = new Paddle(this, kScreenWidth / 2, kScreenHeight / 2);
    //Paddle * right_paddle = new Paddle(this, kScreenWidth / 2, kScreenHeight / 2);

    entigent_->add_object(ball);
    //entigent_->add_object(left_paddle);
    //entigent_->add_object(right_paddle);

    // Main Loop
    while(quit_ == false) {

        // Handle Events
        evengent_->handle_events();

        // Update
        ball->update(delta_timer_.get_ticks());
        //left_paddle->update(delta_timer_.get_ticks());
        //right_paddle->update(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        screen_->clear();
        screen_->render_board();
        ball->render();
        //left_paddle->render();
        //right_paddle->render();

        screen_->update();
    }

    delete(ball);
    //delete(left_paddle);
    //delete(right_paddle);
}

// placeholder functions (not implemented yet)

void Game::process_arguments(int argc, char * argv[])
{

}
