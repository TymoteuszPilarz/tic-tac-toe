//
//  Game.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#ifndef Game_hpp
#define Game_hpp

#include <memory>
#include <vector>

#include "SDL.h"
#include "SDL_mixer.h"
#include "GameMode.hpp"
#include "PlayerTag.hpp"
#include "Board.hpp"

class Game
{
private:
    using windowPtr = std::unique_ptr<SDL_Window, decltype([](SDL_Window* window)
    {
        SDL_DestroyWindow(window);
    })>;

    using rendererPtr = std::unique_ptr<SDL_Renderer, decltype([](SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
    })>;

    windowPtr window;
    rendererPtr renderer;
    std::vector<SDL_Event> mouseEventsQueue;

    SDL_Texture* oVictoryTexture;
    SDL_Texture* xVictoryTexture;
    SDL_Texture* tieTexture;

    Mix_Chunk* oSound;
    Mix_Chunk* xSound;
    Mix_Chunk* victorySound;
    Mix_Chunk* defeatSound;
    Mix_Chunk* tieSound;

    bool running = true;
    bool gameOver = false;
    int turn = 0;

    // Initial settings
    GameMode currentGameMode = GameMode::pve;
    PlayerTag firstPlayer = PlayerTag::player0;
    PlayerTag currentPlayer = firstPlayer;

    std::unique_ptr<Board> board;

    [[nodiscard]] bool playAgain() const;
    bool movePlayer();
    int minimax(int depth, int alpha, int beta, bool isMaximizing);
    bool moveBot();

public:
    Game(int windowWidth, int windowHeight);
    ~Game();
    [[nodiscard]] bool isRunning() const;
    void handleEvents();
    void update();
    void render() const;
};

#endif /* Game_hpp */
