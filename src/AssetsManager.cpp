//
//  AssetsManager.cpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#include <cassert>

#include "AssetsManager.hpp"

AssetsManager& AssetsManager::getInstance()
{
    static AssetsManager assetsManager;
    return assetsManager;
}

void AssetsManager::loadAssets(SDL_Renderer* renderer)
{
    textures.try_emplace(texture::board, AssetsLoader::loadTexture("res/images/board.png", renderer));
    textures.try_emplace(texture::o, AssetsLoader::loadTexture("res/images/o.png", renderer));
    textures.try_emplace(texture::x, AssetsLoader::loadTexture("res/images/x.png", renderer));
    textures.try_emplace(texture::oVictory, AssetsLoader::loadTexture("res/images/o_victory.png", renderer));
    textures.try_emplace(texture::xVictory, AssetsLoader::loadTexture("res/images/x_victory.png", renderer));
    textures.try_emplace(texture::tie, AssetsLoader::loadTexture("res/images/tie.png", renderer));

    sounds.try_emplace(sound::o, AssetsLoader::loadSound("res/sounds/mark_sound.wav"));
    sounds.try_emplace(sound::x, AssetsLoader::loadSound("res/sounds/mark_sound.wav"));
    sounds.try_emplace(sound::victory, AssetsLoader::loadSound("res/sounds/victory_sound.wav"));
    sounds.try_emplace(sound::defeat, AssetsLoader::loadSound("res/sounds/defeat_sound.wav"));
    sounds.try_emplace(sound::tie, AssetsLoader::loadSound("res/sounds/tie_sound.wav"));

    Mix_VolumeChunk(sounds[sound::o].get(), MIX_MAX_VOLUME / 20);
    Mix_VolumeChunk(sounds[sound::x].get(), MIX_MAX_VOLUME / 20);
    Mix_VolumeChunk(sounds[sound::victory].get(), MIX_MAX_VOLUME / 14);
    Mix_VolumeChunk(sounds[sound::defeat].get(), MIX_MAX_VOLUME / 10);
    Mix_VolumeChunk(sounds[sound::tie].get(), MIX_MAX_VOLUME / 3);

    areAssetsLoaded = true;
}

SDL_Texture* AssetsManager::getTexture(texture texture)
{
    assert(areAssetsLoaded);

    return textures[texture].get();
}

Mix_Chunk* AssetsManager::getSound(sound sound)
{
    assert(areAssetsLoaded);

    return sounds[sound].get();
}
