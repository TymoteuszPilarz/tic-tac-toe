cmake_minimum_required(VERSION 3.24)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToe src/main.cpp src/Game.cpp src/AssetsManager.cpp src/Board.cpp src/Field.cpp src/Mark.cpp)

target_include_directories(TicTacToe PRIVATE include)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# link lib
target_link_libraries(TicTacToe PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
