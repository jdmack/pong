#include <fstream>
#include <iostream>

#include "game.h"
#include "util/logger.h"
#include "constants.h"
using namespace std;

int main(int argc, char* argv[])
{
    int exit_code = 0;

    Game * game = new Game;

    game->process_arguments(argc, argv);

    exit_code = game->run();

    delete game;
    game = nullptr;

    return exit_code;
}
