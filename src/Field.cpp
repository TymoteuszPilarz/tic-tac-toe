//
//  Field.cpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 16/02/2022.
//

#include "Field.hpp"

Field::Field(SDL_Renderer* renderer, SDL_Rect area) : mRenderer(renderer), mArea(area), mMark(renderer, area)
{
}

bool Field::mark(PlayerTag playerTag)
{
    if (isMarked())
    {
        return false;
    }

    mMark.setPlayerTag(playerTag);

    return true;
}

void Field::unmark()
{
    mMark.setPlayerTag(PlayerTag::none);
}

bool Field::isMarked() const
{
    return getPlayerTag() != PlayerTag::none;
}

PlayerTag Field::getPlayerTag() const
{
    return mMark.getPlayerTag();
}

bool Field::containsPoint(SDL_Point point) const
{
    if (point.x >= mArea.x && point.x < mArea.x + mArea.w && point.y >= mArea.y && point.y < mArea.y + mArea.h)
    {
        return true;
    }

    return false;
}

void Field::render() const
{
    mMark.render();
}
