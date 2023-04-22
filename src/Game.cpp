//
//  Game.cpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#include <algorithm>

#include "Game.hpp"
#include "SDL_Exception.hpp"
#include "AssetsManager.hpp"

bool Game::playAgain() const
{
    if (!mouseEventsQueue.empty())
    {
        return true;
    }
    
    return false;
}

bool Game::movePlayer()
{
    for (const auto event : mouseEventsQueue)
    {
        const SDL_MouseButtonEvent& mouseEvent = event.button;
        if (mouseEvent.button == SDL_BUTTON_LEFT)
        {
            if (board->mark({mouseEvent.x, mouseEvent.y}, currentPlayer))
            {
                if (currentPlayer == PlayerTag::player0)
                {
                    Mix_PlayChannel(-1, oSound, 0);
                }
                else
                {
                    Mix_PlayChannel(-1, xSound, 0);
                }

                return true;
            }
        }
    }
    
    return false;
}

int Game::minimax(int depth, int alpha, int beta, bool isMaximizing)
{
    PlayerTag winner = board->check();
    
    if (winner == PlayerTag::bot)
    {
        return 10 - depth;
    }
    else if (winner == PlayerTag::player0)
    {
        return -10 + depth;
    }
    else if (turn == 9)
    {
        return 0;
    }
    
    if (isMaximizing)
    {
        int bestScore = -100;
        
        for (int i = 0; i < 3; ++i)
        {
            bool exit = false;
            for (int j = 0; j < 3; ++j)
            {
                if (board->mark(i, j, PlayerTag::bot))
                {
                    ++turn;
                    int score = minimax(depth + 1, alpha, beta, false);
                    
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                    
                    --turn;
                    board->unmark(i, j);
                    
                    if (beta <= alpha)
                    {
                        exit = true;
                        break;
                    }
                }
            }
            if (exit)
            {
                break;
            }
        }
        
        return bestScore;
    }
    else
    {
        int worstScore = 100;
        
        for (int i = 0; i < 3; ++i)
        {
            bool exit = false;
            for (int j = 0; j < 3; ++j)
            {
                if (board->mark(i, j, PlayerTag::player0))
                {
                    ++turn;
                    int score = minimax(depth + 1, alpha, beta, true);
                    
                    worstScore = std::min(worstScore, score);
                    beta = std::min(beta, score);
                    
                    --turn;
                    board->unmark(i, j);
                    
                    if (beta <= alpha)
                    {
                        exit = true;
                        break;
                    }
                }
            }
            if (exit)
            {
                break;
            }
        }
        
        return worstScore;
    }
}

bool Game::moveBot()
{
    int bestScore = -100;
    std::pair bestMove(-1, -1);
    
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board->mark(i, j, PlayerTag::bot))
            {
                ++turn;
                int score = minimax(0, -100, 100, false);
                
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
                
                --turn;
                board->unmark(i, j);
            }
        }
    }
    
    if (bestMove.first == -1)
    {
        return false;
    }
    
    board->mark(bestMove.first, bestMove.second, PlayerTag::bot);
    
    return true;
}

Game::Game(int windowWidth, int windowHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        throw SDL_Exception("SDL could not be initialized", SDL_GetError());
    }
    
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear mTexture filtering not enabled!");
    }
    
    window = windowPtr(SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowHeight, windowHeight, SDL_WINDOW_SHOWN));
    
    if (window == nullptr)
    {
        throw SDL_Exception("Window could not be created", SDL_GetError());
    }
    
    renderer = rendererPtr(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

    if (renderer == nullptr)
    {
        throw SDL_Exception("Renderer could not be created", SDL_GetError());
    }
    
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        throw SDL_Exception("SDL_image could not initialize", IMG_GetError());
    }
    
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        throw SDL_Exception("SDL_mixer could not initialize", Mix_GetError());
    }

    AssetsManager& assetsManager = AssetsManager::getInstance();

    assetsManager.loadAssets(renderer.get());
    
    oVictoryTexture = assetsManager.getTexture(AssetsManager::texture::oVictory);
    xVictoryTexture = assetsManager.getTexture(AssetsManager::texture::xVictory);
    tieTexture = assetsManager.getTexture(AssetsManager::texture::tie);
    
    oSound = assetsManager.getSound(AssetsManager::sound::o);
    xSound = assetsManager.getSound(AssetsManager::sound::x);
    victorySound = assetsManager.getSound(AssetsManager::sound::victory);
    defeatSound = assetsManager.getSound(AssetsManager::sound::defeat);
    tieSound = assetsManager.getSound(AssetsManager::sound::tie);

    board = std::make_unique<Board>(renderer.get(), SDL_Rect{30, 30, windowWidth - 50, windowHeight - 50}, 10);
}

Game::~Game()
{
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::isRunning() const
{
    return running;
}

void Game::handleEvents()
{
    SDL_Event event;
    mouseEventsQueue.clear();
    
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            mouseEventsQueue.push_back(event);
        }
    }
}

void Game::update()
{
    if (gameOver)
    {
        if (playAgain())
        {
            board->reset();
            currentPlayer = firstPlayer;
            turn = 0;
            gameOver = false;
            Mix_HaltChannel(-1);
        }
        
        return;
    }
    
    if (currentGameMode == GameMode::pve)
    {
        if (currentPlayer == PlayerTag::player0)
        {
            if (movePlayer())
            {
                Mix_PlayChannel(-1, oSound, 0);
                currentPlayer = PlayerTag::bot;
                ++turn;
            }
        }
        else
        {
            if (moveBot())
            {
                Mix_PlayChannel(-1, xSound, 0);
                currentPlayer = PlayerTag::player0;
                ++turn;
            }
        }
    }
    else
    {
        if (movePlayer())
        {
            if (currentPlayer == PlayerTag::player0)
            {
                Mix_PlayChannel(-1, oSound, 0);
                currentPlayer = PlayerTag::player1;
            }
            else
            {
                Mix_PlayChannel(-1, xSound, 0);
                currentPlayer = PlayerTag::player0;
            }
            ++turn;
        }
    }
    
    PlayerTag winner = board->check();
    
    if (winner != PlayerTag::none)
    {
        if (currentGameMode == GameMode::pve)
        {
            if (winner == PlayerTag::player0)
            {
                Mix_PlayChannel(-1, victorySound, 0);
            }
            else
            {
                Mix_PlayChannel(-1, defeatSound, 0);
            }
        }
        else
        {
            Mix_PlayChannel(-1, victorySound, 0);
        }
        
        gameOver = true;
    }
    else if (turn == 9)
    {
        Mix_PlayChannel(-1, tieSound, 0);
        gameOver = true;
    }
}

void Game::render() const
{
    SDL_RenderClear(renderer.get());
    
    board->render();
    
    if (gameOver)
    {
        int windowWidth{};
        int windowHeight{};
        SDL_GetWindowSize(window.get(), &windowWidth, &windowHeight);

        SDL_Rect destRect {0, 0, windowWidth, windowHeight};
        
        SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer.get(), &destRect);
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 128);
        
        if (turn == 9 && board->check() == PlayerTag::none)
        {
            destRect = {windowWidth / 2 - 95, windowHeight / 2 - 95, 190, 190};
            SDL_RenderCopy(renderer.get(), tieTexture, nullptr, &destRect);
        }
        else if (currentPlayer == PlayerTag::player0)
        {
            destRect = {windowWidth / 2 - 224, windowHeight / 2 - 95, 448, 190};
            SDL_RenderCopy(renderer.get(), xVictoryTexture, nullptr, &destRect);
        }
        else
        {
            destRect = {windowWidth / 2 - 224, windowHeight / 2 - 95, 448, 190};
            SDL_RenderCopy(renderer.get(), oVictoryTexture, nullptr, &destRect);
        }
    }
    
    SDL_RenderPresent(renderer.get());
}
