//
//  Mark.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 16/02/2022.
//

#ifndef Mark_hpp
#define Mark_hpp

#include "SDL.h"
#include "PlayerTag.hpp"

class Mark
{
private:
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    SDL_Rect mArea;

    PlayerTag mPlayerTag;
    
public:
    Mark(SDL_Renderer* renderer, SDL_Rect area, PlayerTag playerTag = PlayerTag::none);

    Mark(const Mark&) = delete;
    Mark(Mark&&) = default;
    Mark& operator=(const Mark&) = delete;
    Mark& operator=(Mark&&) = default;

    void setPlayerTag(PlayerTag playerTag);
    [[nodiscard]] PlayerTag getPlayerTag() const;

    void render() const;
};

#endif /* Mark_hpp */
