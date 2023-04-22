//
//  AssetsManager.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#ifndef AssetsManager_hpp
#define AssetsManager_hpp

#include <unordered_map>

#include "SDL.h"
#include "SDL_mixer.h"
#include "AssetsLoader.hpp"

class AssetsManager
{
public:
    enum class texture {board, o, x, oVictory, xVictory, tie};
    enum class sound {o, x, victory, defeat, tie};

private:
    bool areAssetsLoaded = false;

    std::unordered_map<texture,  AssetsLoader::texturePtr> textures;
    std::unordered_map<sound, AssetsLoader::chunkPtr> sounds;
    
    AssetsManager() = default;
    ~AssetsManager() = default;
    
public:
    static AssetsManager& getInstance();

    void loadAssets(SDL_Renderer* renderer);

    [[nodiscard]] SDL_Texture* getTexture(texture texture);
    [[nodiscard]] Mix_Chunk* getSound(sound sound);
};

#endif /* AssetsManager_hpp */
