#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********** TEST GAME_IS_OVER ********** */
int test_game_is_over()
{

    // default game solution
    game g1 = game_new_empty_ext(6, 6, true, true);

    if ((game_get_current_nb_tents_all(g1)) == (game_get_expected_nb_tents_all(g1)) && (game_is_over(g1) == true)) {
        game_delete(g1);
        return EXIT_SUCCESS;
    } else {
        game_delete(g1);
        return EXIT_FAILURE;
    }
}

/* ********** TEST GAME_RESTART ********** */
int test_game_restart()
{
    //default game
    game g1 = game_new_empty();
    // play a tent
    game_play_move(g1, 0, 0, TENT);
    // play a grass
    game_play_move(g1, 7, 7, GRASS);
    // restart the game
    game_restart(g1);
    // since we restarted the game , the tent and the grass we played should no longer be and the squares should be reseted back to EMPTY
    if (game_get_current_nb_tents_all(g1) == 0 && game_get_square(g1, 7, 7) == EMPTY) {
        game_delete(g1);
        return EXIT_SUCCESS;
    } else {
        game_delete(g1);
        return EXIT_FAILURE;
    }
}

int test_game_get_current_nb_tents_all()
{
    //default game
    game g1 = game_new_empty();
    // play a tent
    game_play_move(g1, 0, 0, TENT);

    // since we played only a tent , the overall number of tents should be one
    if (game_get_current_nb_tents_all(g1) == 1) {
        game_delete(g1);
        return EXIT_SUCCESS;
    }
    game_delete(g1);
    return EXIT_FAILURE;
}

/* ********** TEST GAME_CURRENT_NB_TENTS_ROW ********** */

int test_game_get_current_nb_tents_row()
{
    //default game
    game g1 = game_default_solution();

    // square(0,0) , square (0,3) and square(0,6) are TENTS in the first row of the default game

    if ((game_get_square(g1, 0, 0) == TENT) && (game_get_square(g1, 0, 3) == TENT) && (game_get_square(g1, 0, 6) == TENT) && (game_get_current_nb_tents_row(g1, 0) == 3)) {
        game_delete(g1);
        return EXIT_SUCCESS;
    } else {
        game_delete(g1);
        return EXIT_FAILURE;
    }
}

/* ********** TEST GAME_CURRENT_NB_TENTS_COL ********** */
int test_game_get_current_nb_tents_col()
{
    //default game
    game g1 = game_default_solution();
    // square(0,0) , square (2,0),square(4,0) and square(6,0),are TENTS in the first row of the default game
    if ((game_get_square(g1, 0, 0) == TENT) && (game_get_square(g1, 2, 0) == TENT) && (game_get_square(g1, 4, 0) == TENT) && (game_get_square(g1, 6, 0) == TENT) && (game_get_current_nb_tents_col(g1, 0) == 4)) {
        game_delete(g1);
        return EXIT_SUCCESS;
    }
    game_delete(g1);
    return EXIT_FAILURE;
}

/* ********** TEST GAME_PRINT ********** */
int test_game_print()
{
    //default game
    game g1 = game_default();
    // printing the default game
    game_print(g1);
    game_delete(g1);
    return EXIT_SUCCESS;
}

/* ********** TEST GAME_IS_WRAPPING ********** */

bool test_game_is_wrapping()
{
    game g1 = game_new_empty_ext(6, 6, true, true);
    game g2 = game_new_empty_ext(6, 6, false, true);

    if (game_is_wrapping(g1) == true && game_is_wrapping(g2) == false) {
        game_delete(g1);
        game_delete(g2);
        return EXIT_SUCCESS;
    } else {
        game_delete(g1);
        game_delete(g2);
        return EXIT_FAILURE;
    }
}

/* ********** TEST GAME_IS_DIAGADJ ********** */

bool test_game_is_diagadj()
{
    game g1 = game_new_empty_ext(6, 6, true, true);
    game g2 = game_new_empty_ext(6, 6, false, false);

    if (game_is_diagadj(g1) == true && game_is_diagadj(g2) == false) {
        game_delete(g1);
        game_delete(g2);
        return EXIT_SUCCESS;
    } else {
        game_delete(g1);
        game_delete(g2);
        return EXIT_FAILURE;
    }
}

int main(int argc, char* argv[])
{

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    if (strcmp("game_is_over", argv[1]) == 0) {
        return test_game_is_over();
    }
    if (strcmp("game_restart", argv[1]) == 0) {
        return test_game_restart();
    }
    if (strcmp("game_current_tents_all", argv[1]) == 0) {
        return test_game_get_current_nb_tents_all();
    }
    if (strcmp("game_current_tents_row", argv[1]) == 0) {
        return test_game_get_current_nb_tents_row();
    }
    if (strcmp("game_current_tents_col", argv[1]) == 0) {
        return test_game_get_current_nb_tents_col();
    }
    if (strcmp("game_print", argv[1]) == 0) {
        return test_game_print();
    }
    if (strcmp("game_is_wrapping", argv[1]) == 0) {
        return test_game_is_wrapping();
    }
    if (strcmp("game_is_diagadj", argv[1]) == 0) {
        return test_game_is_diagadj();
    }
}
