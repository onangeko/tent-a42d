#Specify the cmake version used by VPL
cmake_minimum_required(VERSION 3.7)
enable_testing()
#Create the projects
project(game_text C)
#Put standard options
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${game_text_SOURCE_DIR}/cmake)
#Create library
add_library(libgame game.o game_aux.c)
#Set flags for compiling
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
#Put executables with dependencies on projets
add_executable(game_text game_text.c)
#Set links to math library used in both projets
target_link_libraries(game_text libgame)
