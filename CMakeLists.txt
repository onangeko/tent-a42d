#Specify the cmake version used by VPL
cmake_minimum_required(VERSION 3.7)



#Enable tests
enable_testing()

add_executable(game_test_edatrier game_test_edatrier.c)
add_test(game_test_edatrier_dummy ./game_test_edatrier dummy)

add_executable(game_test_mlecoeuvre game_test_mlecoeuvre.c)
add_test(test_game_get_square ./game_test_mlecoeuvre game_get_square)
add_test(test_game_set_square ./game_test_mlecoeuvre game_set_square)

add_executable(game_test_bjgiraud game_test_bjgiraud.c)
add_test(test_bjgiraud_dummy ./game_test_bjgiraud dummy)

add_executable(game_test_onangeko game_test_onangeko.c)
add_test(test_onangeko_dummy ./game_test_onangeko dummy)

#Create the projects
project(game_text C)
include(CTest)
#Put standard options
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${game_text_SOURCE_DIR}/cmake)
#Create library
add_library(game game.o game_aux.c)
#Set flags for compiling
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
#Put executables with dependencies on projets
add_executable(game_text game_text.c)
#Set links to math library used in both projets
target_link_libraries(game_text game)
target_link_libraries(game_test_mlecoeuvre game)

    