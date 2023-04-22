//
//  AssetsLoader.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#ifndef AssetsLoader_hpp
#define AssetsLoader_hpp

#include <string>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_Exception.hpp"

class AssetsLoader
{
public:
    using texturePtr = std::unique_ptr<SDL_Texture, decltype([](SDL_Texture* texture)
    {
        SDL_DestroyTexture(texture);
    })>;

    using chunkPtr = std::unique_ptr<Mix_Chunk, decltype([](Mix_Chunk* chunk)
    {
        Mix_FreeChunk(chunk);
    })>;

    [[nodiscard]] static texturePtr loadTexture(const char* filePath, SDL_Renderer* renderer)
    {
        SDL_Surface* surface = IMG_Load(filePath);

        if (surface == nullptr)
        {
            throw SDL_Exception(std::string("Unable to load image: ") + filePath, IMG_GetError());
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == nullptr)
        {
            SDL_FreeSurface(surface);
            throw SDL_Exception(std::string("Unable to create mTexture from: ") + filePath, SDL_GetError());
        }

        return texturePtr(texture);
    }

    [[nodiscard]] static texturePtr loadTexture(const std::string& filePath, SDL_Renderer* renderer)
    {
        return loadTexture(filePath.c_str(), renderer);
    }

    [[nodiscard]] static chunkPtr loadSound(const char* filePath)
    {
        Mix_Chunk* chunk = Mix_LoadWAV(filePath);
        if (chunk == nullptr)
        {
            throw SDL_Exception(std::string("Unable to load sound: ") + filePath, Mix_GetError());
        }

        return chunkPtr(chunk);
    }

    [[nodiscard]] static chunkPtr loadSound(const std::string& filePath)
    {
        return loadSound(filePath.c_str());
    }
};

#endif /* AssetsLoader_hpp */
