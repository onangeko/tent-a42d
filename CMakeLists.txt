#Specify the cmake version used by VPL
cmake_minimum_required(VERSION 3.7)

#Enable tests
enable_testing()

add_executable(game_test_edatrier game_test_edatrier.c)
add_test(game_test_edatrier_dummy ./game_test_edatrier dummy)

add_executable(game_test_mlecoeuvre game_test_mlecoeuvre.c)
add_test(test_game_get_square ./game_test_mlecoeuvre game_get_square)
add_test(test_game_set_square ./game_test_mlecoeuvre game_set_square)
add_test(test_game_fill_grass_row ./game_test_mlecoeuvre game_fill_grass_row)
add_test(test_game_fill_grass_col ./game_test_mlecoeuvre game_fill_grass_col)
add_test(test_game_play_move ./game_test_mlecoeuvre game_play_move)
add_test(test_game_check_move ./game_test_mlecoeuvre game_check_move)

add_executable(game_test_bjgiraud game_test_bjgiraud.c game.o)
add_test(test_bjgiraud_test_game_get_expected_nb_tents_row ./game_test_bjgiraud test_game_get_expected_nb_tents_row)
add_test(test_bjgiraud_test_game_get_expected_nb_tents_all ./game_test_bjgiraud test_game_get_expected_nb_tents_all)
add_test(test_bjgiraud_test_game_get_expected_nb_tents_col ./game_test_bjgiraud test_game_get_expected_nb_tents_col)
add_test(test_bjgiraud_test_game_set_expected_nb_tents_row ./game_test_bjgiraud test_game_set_expected_nb_tents_row)
add_test(test_bjgiraud_test_game_set_expected_nb_tents_col ./game_test_bjgiraud test_game_set_expected_nb_tents_col)

add_executable(game_test_onangeko game.o game_test_onangeko.c)
add_test(test_onangeko_game_is_over ./game_test_onangeko game_is_over)
add_test(test_onangeko_game_restart ./game_test_onangeko game_restart)
add_test(test_game_get_current_nb_tents_all ./game_test_onangeko game_current_tents_all)
add_test(test_game_get_current_nb_tents_row ./game_test_onangeko game_current_tents_row)
add_test(test_game_get_current_nb_tents_col ./game_test_onangeko game_current_tents_col)

#Create the projects

project(game_text C)

include(CTest)

#Put standard options

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${game_text_SOURCE_DIR}/cmake)

#Create library

add_library(game game00.o game_aux.c)

#Set flags for compiling

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

#Put executables with dependencies on projets

add_executable(game_text game_text.c)

#Set links to math library used in both projets

target_link_libraries(game_text game)
target_link_libraries(game_test_onangeko game)
target_link_libraries(game_test_bjgiraud game)
target_link_libraries(game_test_mlecoeuvre game)

    