cmake_minimum_required(VERSION 3.10)
project(racingGame C)

set(CMAKE_C_STANDARD 11)

add_executable(fullGame main.c welcomeWindow.c gameWindow.c windowManager.c geometry.c goodbyeWindow.c)
target_link_libraries(fullGame csfml-graphics csfml-audio csfml-window csfml-system m)