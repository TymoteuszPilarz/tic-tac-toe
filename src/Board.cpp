//
//  Board.cpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 16/02/2022.
//

#include "Board.hpp"
#include "AssetsManager.hpp"

Board::Board(SDL_Renderer* renderer, SDL_Rect area, int gap) : renderer(renderer)
{
    const int fieldWidth = (area.w - 2 * gap) / 3;
    const int fieldHeight = (area.h - 2 * gap) / 3;

    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            fields[row][column] = std::make_unique<Field>(renderer, SDL_Rect{area.x + column * (fieldWidth + gap), area.y + row * (fieldHeight + gap), fieldWidth, fieldHeight});
        }
    }
}

bool Board::mark(int row, int column, PlayerTag playerTag)
{
    assert(row >= 0 && row < 3);
    assert(column >= 0 && column < 3);

    return fields[row][column]->mark(playerTag);
}

bool Board::mark(SDL_Point position, PlayerTag playerTag)
{
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (fields[row][column]->containsPoint(position))
            {
                return mark(row, column, playerTag);
            }
        }
    }

    return false;
}

void Board::unmark(int row, int column)
{
    assert(row >= 0 && row < 3);
    assert(column >= 0 && column < 3);

    fields[row][column]->unmark();
}

PlayerTag Board::check() const
{
    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (fields[i][0]->isMarked() && fields[i][1]->isMarked() && fields[i][2]->isMarked())
        {
            if (static_cast<int>(fields[i][0]->getPlayerTag()) == static_cast<int>(fields[i][1]->getPlayerTag()) && static_cast<int>(fields[i][1]->getPlayerTag()) == static_cast<int>(fields[i][2]->getPlayerTag()))
            {
                return fields[i][0]->getPlayerTag();
            }
        }
    }

    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (fields[0][i]->isMarked() && fields[1][i]->isMarked() && fields[2][i]->isMarked())
        {
            if (static_cast<int>(fields[0][i]->getPlayerTag()) == static_cast<int>(fields[1][i]->getPlayerTag()) && static_cast<int>(fields[1][i]->getPlayerTag()) == static_cast<int>(fields[2][i]->getPlayerTag()))
            {
                return fields[0][i]->getPlayerTag();
            }
        }
    }

    // Check first diagonal
    if (fields[0][0]->isMarked() && fields[1][1]->isMarked() && fields[2][2]->isMarked())
    {
        if (static_cast<int>(fields[0][0]->getPlayerTag()) == static_cast<int>(fields[1][1]->getPlayerTag()) && static_cast<int>(fields[1][1]->getPlayerTag()) == static_cast<int>(fields[2][2]->getPlayerTag()))
        {
            return fields[0][0]->getPlayerTag();
        }
    }

    // Check second diagonal
    if (fields[0][2]->isMarked() && fields[1][1]->isMarked() && fields[2][0]->isMarked())
    {
        if (static_cast<int>(fields[0][2]->getPlayerTag()) == static_cast<int>(fields[1][1]->getPlayerTag()) && static_cast<int>(fields[1][1]->getPlayerTag()) == static_cast<int>(fields[2][0]->getPlayerTag()))
        {
            return fields[0][2]->getPlayerTag();
        }
    }
    
    return PlayerTag::none;
}

void Board::reset()
{
    for (auto& row : fields)
    {
        for (auto& column : row)
        {
            column->unmark();
        }
    }
}

void Board::render() const
{
    SDL_RenderCopy(renderer, AssetsManager::getInstance().getTexture(AssetsManager::texture::board), nullptr, nullptr);
    
    for (const auto& row : fields)
    {
        for (const auto& column : row)
        {
            if (column != nullptr)
            {
                column->render();
            }
        }
    }
}
