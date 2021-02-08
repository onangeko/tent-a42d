#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********** TEST GET_SQUARE ********** */
bool test_game_get_square(game g)
{
    //EMPTY square
    square s = game_get_square(g, 0, 0);
    if (s != EMPTY)
        return false;
    //TREE square
    s = game_get_square(g, 0, 5);
    if (s != TREE)
        return false;
    //TENT square
    game_set_square(g, 0, 0, TENT);
    s = game_get_square(g, 0, 0);
    if (s != TENT) {
        return false;
    }
    //GRASS square
    game_set_square(g, 0, 0, GRASS);
    s = game_get_square(g, 0, 0);
    if (s != GRASS) {
        return false;
    }
    return true;
}

/* ********** TEST SET_SQUARE ********** */
bool test_game_set_square(game g)
{
    //EMPTY square
    game_set_square(g, 0, 0, EMPTY);
    square s = game_get_square(g, 0, 0);
    if (s != EMPTY)
        return false;
    //TENT square
    game_set_square(g, 0, 0, TENT);
    s = game_get_square(g, 0, 0);
    if (s != TENT) {
        return false;
    }
    //GRASS square
    game_set_square(g, 0, 0, GRASS);
    s = game_get_square(g, 0, 0);
    if (s != GRASS) {
        return false;
    }
    return true;
}

/* ********** TEST FILL_GRASS_ROW ********** */
bool test_game_fill_grass_row(game g)
{
    // fill [0] row with grass
    game_fill_grass_row(g, 0);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        // square(0,4) and square(0,5) are trees in default game
        if (i != 4 && i != 5 && game_get_square(g, 0, i) != GRASS) {
            return false;
        }
    }
    return true;
}

/* ********** TEST FILL_GRASS_COL ********** */
bool test_game_fill_grass_col(game g)
{
    // fill [0] col with grass
    game_fill_grass_col(g, 0);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        // square(1,0) and square(3,0) and square(5,0) and square(7,0) are trees in default game
        if (i != 1 && i != 3 && i != 5 && i != 7 && game_get_square(g, i, 0) != GRASS) {
            return false;
        }
    }
    return true;
}

/* ********** TEST PLAY_MOVE ********** */
bool test_game_play_move(game g)
{
    //Set tent on square(0,0)
    game_play_move(g, 0, 0, TENT);
    square s = game_get_square(g, 0, 0);
    if (s != TENT)
        return false;
    //Set grass on square(0,0)
    game_play_move(g, 0, 0, GRASS);
    s = game_get_square(g, 0, 0);
    if (s != GRASS)
        return false;
    //Set empty on square(0,0)
    game_play_move(g, 0, 0, EMPTY);
    s = game_get_square(g, 0, 0);
    if (s != EMPTY)
        return false;
    return true;
}

/* ********** TEST CHECK_MOVE ********** */
bool test_game_check_move(game g, game g_new)
{
    /// No diagadj, No wrapping settings
    //Illegal moves
    //* plant a tree
    if (game_check_move(g, 0, 0, TREE) != ILLEGAL)
        return false;
    //* plant a tent on a tree
    if (game_check_move(g, 1, 0, TENT) != ILLEGAL)
        return false;
    //* put a grass on a tree
    if (game_check_move(g, 1, 0, GRASS) != ILLEGAL)
        return false;
    //* erase square on a tree
    if (game_check_move(g, 1, 0, EMPTY) != ILLEGAL)
        return false;
    //Losing moves
    //* plant tent adjacent to another orthogonally
    game_play_move(g, 0, 6, TENT);
    if (game_check_move(g, 0, 7, TENT) != LOSING)
        return false;
    //* plant tent adjacent to another diagonally without diagadj
    game_play_move(g, 2, 3, TENT);
    if (game_check_move(g, 3, 4, TENT) != LOSING)
        return false;
    //* plant n+1 tents when n tents are expected
    if (game_check_move(g, 1, 1, TENT) != LOSING)
        return false;
    //* put grass when number of empty squares is not enough to reach the expected number of tents
    game_play_move(g, 0, 1, GRASS);
    game_play_move(g, 0, 2, GRASS);
    game_play_move(g, 0, 3, GRASS);
    if (game_check_move(g, 0, 6, GRASS) != LOSING)
        return false;
    game_restart(g);
    //* replace a tent by a grass and empty squares is not enough to reach the expected number of tents
    game_play_move(g, 0, 0, TENT);
    game_play_move(g, 0, 1, GRASS);
    game_play_move(g, 0, 2, GRASS);
    game_play_move(g, 0, 3, TENT);
    game_play_move(g, 0, 6, TENT);
    game_play_move(g, 0, 7, GRASS);
    if (game_check_move(g, 0, 6, GRASS) != LOSING)
        return false;
    game_restart(g);
    //* surround a tree with grass
    game_play_move(g, 2, 3, GRASS);
    game_play_move(g, 1, 4, GRASS);
    game_play_move(g, 2, 5, GRASS);
    if (game_check_move(g, 3, 4, GRASS) != LOSING)
        return false;
    game_restart(g);
    //* plant a tent not adjacent to a tree
    if (game_check_move(g, 0, 1, TENT) != LOSING)
        return false;
    //Regular moves
    if (game_check_move(g, 0, 0, TENT) != REGULAR)
        return false;
    if (game_check_move(g, 1, 1, GRASS) != REGULAR)
        return false;
    if (game_check_move(g, 0, 6, EMPTY) != REGULAR)
        return false;
    game_play_move(g, 0, 0, TENT);
    game_play_move(g, 0, 3, TENT);
    game_play_move(g, 0, 6, TENT);
    if (game_check_move(g, 0, 1, GRASS) != REGULAR)
        return false;

    /// diagadj and wrapping settings
    //Losing moves
    //* surround a tree with grass (wrapping)
    game_play_move(g_new, 2, 0, GRASS);
    game_play_move(g_new, 4, 0, GRASS);
    game_play_move(g_new, 3, 1, GRASS);
    if (game_check_move(g_new, 3, 7, GRASS) != LOSING)
        return false;
    game_restart(g_new);
    game_play_move(g_new, 6, 0, GRASS);
    game_play_move(g_new, 7, 1, GRASS);
    game_play_move(g_new, 7, 7, GRASS);
    if (game_check_move(g_new, 0, 0, GRASS) != LOSING)
        return false;
    //Regular moves
    //* plant tent adjacent to a tree (wrapping)
    if (game_check_move(g_new, 7, 4, TENT) != REGULAR)
        return false;
    //* plant tent adjacent to another diagonally with diagadj
    game_play_move(g_new, 2, 3, TENT);
    if (game_check_move(g_new, 3, 4, TENT) != REGULAR)
        return false;
    game_restart(g_new);
    return true;
}

bool test_game_redo(game g)
{
    game_play_move(g, 0, 0, TENT);
    game_undo(g);
    game_redo(g);
    return game_get_square(g, 0, 0) == TENT;
}

game game_default_new()
{
    //Special configuration for new fonctions (not a legal game)
    game g = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, true, true);
    game_set_square(g, 0, 4, TREE);
    game_set_square(g, 0, 5, TREE);
    game_set_expected_nb_tents_row(g, 0, 1);
    //row 1
    game_set_square(g, 1, 0, TREE);
    game_set_square(g, 1, 7, TREE);
    game_set_expected_nb_tents_row(g, 1, 1);
    //row 2
    game_set_square(g, 2, 4, TREE);
    game_set_expected_nb_tents_row(g, 2, 1);
    //row 3
    game_set_square(g, 3, 0, TREE);
    game_set_square(g, 3, 5, TREE);
    game_set_expected_nb_tents_row(g, 3, 1);
    //row 4
    game_set_square(g, 4, 1, TREE);
    game_set_expected_nb_tents_row(g, 4, 1);
    //row 5
    game_set_square(g, 5, 0, TREE);
    game_set_square(g, 5, 4, TREE);
    game_set_square(g, 5, 6, TREE);
    game_set_expected_nb_tents_row(g, 5, 1);
    //row 6
    //No tree
    game_set_expected_nb_tents_row(g, 6, 1);
    //row 7
    game_set_square(g, 7, 0, TREE);
    game_set_expected_nb_tents_row(g, 7, 1);

    //Set expected number of tents for columns
    //column 0
    game_set_expected_nb_tents_col(g, 0, 1);
    //column 1
    game_set_expected_nb_tents_col(g, 1, 1);
    //column 2
    game_set_expected_nb_tents_col(g, 2, 1);
    //column 3
    game_set_expected_nb_tents_col(g, 3, 1);
    //column 4
    game_set_expected_nb_tents_col(g, 4, 1);
    //column 5
    game_set_expected_nb_tents_col(g, 5, 1);
    //column 6
    game_set_expected_nb_tents_col(g, 6, 1);
    //column 7
    game_set_expected_nb_tents_col(g, 7, 1);
    return g;
}

int main(int argc, char* argv[])
{
    //default game
    game g = game_default();
    game g_new = game_default_new();

    bool ok = false;
    if (strcmp("game_get_square", argv[1]) == 0)
        ok = test_game_get_square(g);
    else if (strcmp("game_set_square", argv[1]) == 0)
        ok = test_game_set_square(g);
    else if (strcmp("game_fill_grass_row", argv[1]) == 0)
        ok = test_game_fill_grass_row(g);
    else if (strcmp("game_fill_grass_col", argv[1]) == 0)
        ok = test_game_fill_grass_col(g);
    else if (strcmp("game_play_move", argv[1]) == 0)
        ok = test_game_play_move(g);
    else if (strcmp("game_check_move", argv[1]) == 0)
        ok = test_game_check_move(g, g_new);
    else if (strcmp("game_redo", argv[1]) == 0)
        ok = test_game_redo(g);
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    game_save(g, "test.txt");
    game_save(game_default_solution(), "test_solution.txt");
    game_delete(g);
    game_delete(g_new);
    // print test result
    if (ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
