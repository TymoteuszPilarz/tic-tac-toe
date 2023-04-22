//
//  Field.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 16/02/2022.
//

#ifndef Field_hpp
#define Field_hpp

#include "SDL.h"
#include "PlayerTag.hpp"
#include "Mark.hpp"

class Field
{
private:
    SDL_Renderer* mRenderer;

    SDL_Rect mArea;
    Mark mMark;

public:
    explicit Field(SDL_Renderer* renderer, SDL_Rect area);

    Field(const Field&) = delete;
    Field(Field&&) = default;
    Field& operator=(const Field&) = delete;
    Field& operator=(Field&&) = default;

    bool mark(PlayerTag playerTag);
    void unmark();

    [[nodiscard]] PlayerTag getPlayerTag() const;
    [[nodiscard]] bool isMarked() const;
    [[nodiscard]] bool containsPoint(SDL_Point point) const;

    void render() const;
};

#endif /* Field_hpp */
