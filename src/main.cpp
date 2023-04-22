//
//  main.cpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#include <iostream>

#include "Game.hpp"

int main(int argc, char* args[])
{
    try
    {
        Game game(601, 601);
        while (game.isRunning())
        {
            game.handleEvents();
            game.update();
            game.render();
        }
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
