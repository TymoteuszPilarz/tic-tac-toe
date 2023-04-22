//
//  Mark.cpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 16/02/2022.
//

#include "Mark.hpp"
#include "AssetsManager.hpp"

Mark::Mark(SDL_Renderer* renderer, SDL_Rect area, PlayerTag playerTag) : mRenderer(renderer), mArea(area)
{
    setPlayerTag(playerTag);
}

void Mark::setPlayerTag(PlayerTag playerTag)
{
    mPlayerTag = playerTag;

    if (playerTag == PlayerTag::player0)
    {
        mTexture = AssetsManager::getInstance().getTexture(AssetsManager::texture::o);
    }
    else if (playerTag == PlayerTag::player1 || playerTag == PlayerTag::bot)
    {
        mTexture = AssetsManager::getInstance().getTexture(AssetsManager::texture::x);
    }
    else
    {
        mTexture = nullptr;
    }
}

PlayerTag Mark::getPlayerTag() const
{
    return mPlayerTag;
}

void Mark::render() const
{
    if (getPlayerTag() != PlayerTag::none)
    {
        SDL_RenderCopy(mRenderer, mTexture, nullptr, &mArea);
    }
}
