//
//  SDL_Exception.hpp
//  TicTacToe
//
//  Created by Tymoteusz Pilarz on 15/02/2022.
//

#ifndef SDL_Exception_hpp
#define SDL_Exception_hpp

#include <exception>
#include <string>

class SDL_Exception: public std::exception
{
private:
    std::string msg;
    
public:
    explicit SDL_Exception(const char* message, const char* sdlError) : msg(std::string("Message: ") + message + '\n' + "SDL Error: " + sdlError + '\n') {}
    explicit SDL_Exception(const std::string& message, const char* sdlError) : msg(std::string("Message: ") + message + '\n' + "SDL Error: " + sdlError + '\n') {}
    [[nodiscard]] const char* what() const noexcept override
    {
        return msg.c_str();
    }
};

#endif /* SDL_Exception_hpp */
