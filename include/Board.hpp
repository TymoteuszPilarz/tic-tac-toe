//
//  Board.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 16/02/2022.
//

#ifndef Board_hpp
#define Board_hpp

#include <array>
#include <memory>

#include "SDL.h"
#include "PlayerTag.hpp"
#include "Field.hpp"

class Board
{
private:
    SDL_Renderer* renderer = nullptr;

    std::array<std::array<std::unique_ptr<Field>, 3>, 3> fields;
    
public:
    Board(SDL_Renderer* renderer, SDL_Rect area, int gap = 0);

    Board(const Board&) = delete;
    Board(Board&&) = default;
    Board& operator=(const Board&) = delete;
    Board& operator=(Board&&) = default;

    bool mark(int row, int column, PlayerTag playerTag);
    bool mark(SDL_Point position, PlayerTag playerTag);
    void unmark(int row, int column);

    [[nodiscard]] PlayerTag check() const;

    void reset();
    void render() const;
};

#endif /* Board_hpp */
