#Specify the cmake version used by VPL
cmake_minimum_required(VERSION 3.7)

#Enable tests
enable_testing()

add_executable(game_test_edatrier game_test_edatrier.c)
add_test(test_edatrier_game_new ./game_test_edatrier game_new)
add_test(test_edatrier_game_new_ext ./game_test_edatrier game_new_ext)
add_test(test_edatrier_game_new_empty ./game_test_edatrier game_new_empty)
add_test(test_edatrier_game_new_empty_ext ./game_test_edatrier game_new_empty_ext)
add_test(test_edatrier_game_copy ./game_test_edatrier game_copy)
add_test(test_edatrier_game_equal ./game_test_edatrier game_equal)
add_test(test_edatrier_game_delete ./game_test_edatrier game_delete)
add_test(test_edatrier_game_default_solution ./game_test_edatrier game_default_solution)
add_test(test_edatrier_game_undo ./game_test_edatrier game_undo)

add_executable(game_test_mlecoeuvre game_test_mlecoeuvre.c)
add_test(test_mlecoeuvre_game_get_square ./game_test_mlecoeuvre game_get_square)
add_test(test_mlecoeuvre_game_set_square ./game_test_mlecoeuvre game_set_square)
add_test(test_mlecoeuvre_game_fill_grass_row ./game_test_mlecoeuvre game_fill_grass_row)
add_test(test_mlecoeuvre_game_fill_grass_col ./game_test_mlecoeuvre game_fill_grass_col)
add_test(test_mlecoeuvre_game_play_move ./game_test_mlecoeuvre game_play_move)
add_test(test_mlecoeuvre_game_check_move ./game_test_mlecoeuvre game_check_move)
add_test(test_mlecoeuvre_game_redo ./game_test_mlecoeuvre game_redo)

add_executable(game_test_bjgiraud game_test_bjgiraud.c)
add_test(test_bjgiraud_game_get_expected_nb_tents_row ./game_test_bjgiraud game_get_expected_nb_tents_row)
add_test(test_bjgiraud_game_get_expected_nb_tents_all ./game_test_bjgiraud game_get_expected_nb_tents_all)
add_test(test_bjgiraud_game_get_expected_nb_tents_col ./game_test_bjgiraud game_get_expected_nb_tents_col)
add_test(test_bjgiraud_game_set_expected_nb_tents_row ./game_test_bjgiraud game_set_expected_nb_tents_row)
add_test(test_bjgiraud_game_set_expected_nb_tents_col ./game_test_bjgiraud game_set_expected_nb_tents_col)
add_test(test_bjgiraud_game_default ./game_test_bjgiraud game_default)
add_test(test_bjgiraud_game_nb_rows ./game_test_bjgiraud game_nb_rows)
add_test(test_bjgiraud_game_nb_cols ./game_test_bjgiraud game_nb_cols)
add_test(test_bjgiraud_game_save_and_load ./game_test_bjgiraud game_save_and_load)

add_executable(game_test_onangeko game_test_onangeko.c)
add_test(test_onangeko_game_is_over ./game_test_onangeko game_is_over)
add_test(test_onangeko_game_restart ./game_test_onangeko game_restart)
add_test(test_onangeko_game_get_current_nb_tents_all ./game_test_onangeko game_current_tents_all)
add_test(test_onangeko_game_get_current_nb_tents_row ./game_test_onangeko game_current_tents_row)
add_test(test_onangeko_game_get_current_nb_tents_col ./game_test_onangeko game_current_tents_col)
add_test(test_onangeko_game_print ./game_test_onangeko game_print)
add_test(test_onangeko_game_is_wrapping ./game_test_onangeko game_is_wrapping)
add_test(test_onangeko_game_is_diagadj ./game_test_onangeko game_is_diagadj)




#Create the projects

project(game_text C)

include(CTest)

#Solve dependencies

find_package(SDL2 REQUIRED)
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS})
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2_image)

#Put standard options

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${game_text_SOURCE_DIR}/cmake)

#Create library

add_library(game game.c game_aux.c game_tools.c queue.c game_private.c game_ext.c)
add_library(sdl model.c)

#Set flags for compiling

set(CMAKE_C_FLAGS "-DNDEBUG -O3 -std=c99 -g --coverage -Wall")

#Put executables with dependencies on projets
include_directories(${SDL2_ALL_INC})
add_executable(game_text game_text.c)

add_executable(game_solve game_solve.c)

add_executable(game_sdl main.c)

#Set links to math library used in both projets

target_link_libraries(game_solve game)
target_link_libraries(game_text game)
target_link_libraries(game_test_onangeko game)
target_link_libraries(game_test_bjgiraud game)
target_link_libraries(game_test_mlecoeuvre game)
target_link_libraries(game_test_edatrier game)

target_link_libraries(game_sdl ${SDL2_ALL_LIBS} sdl)


    