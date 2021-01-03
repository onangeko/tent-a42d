#include "game_aux.h"
#include "game_ext.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_game_new(square* squares, uint* nb_tents_row, uint* nb_tents_col)
{
    //Creates the game using the arguments as parameters
    game g = game_new(squares, nb_tents_row, nb_tents_col);
    /*
    Tests, for each square, if the value is the same as the parameters we put in 
    and if the number of expected tents expected is correct for each row and column
    */
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (game_get_expected_nb_tents_row(g, i) != nb_tents_row[i]) {
            game_delete(g);
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != squares[(i * 8) + j] || game_get_expected_nb_tents_col(g, j) != nb_tents_col[j]) {
                game_delete(g);
                return false;
            }
    }
    game_delete(g);
    return true;
}

bool test_game_new_ext(square* squares, uint* nb_tents_row, uint* nb_tents_col, uint nb_rows, uint nb_cols, bool wrapping, bool diagadj)
{
    //Creates the game using the arguments as parameters
    game g = game_new_ext(nb_rows, nb_cols, squares, nb_tents_row, nb_tents_col, wrapping, diagadj);
    /*
    Tests, for each square, if the value is the same as the parameters we put in 
    and if the number of expected tents expected is correct for each row and column
    */
    if (game_nb_rows(g) != nb_rows)
        return false;
    if (game_nb_cols(g) != nb_cols)
        return false;
    if (game_is_wrapping(g) != wrapping)
        return false;
    if (game_is_diagadj(g) != diagadj)
        return false;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (game_get_expected_nb_tents_row(g, i) != nb_tents_row[i]) {
            game_delete(g);
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != squares[(i * 8) + j] || game_get_expected_nb_tents_col(g, j) != nb_tents_col[j]) {
                game_delete(g);
                return false;
            }
    }
    game_delete(g);
    return true;
}

bool test_game_new_empty(void)
{
    game g = game_new_empty();
    //Tests, for each square, if the value is EMPTY and if the number of expected tents is 0 for each row and column
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (game_get_expected_nb_tents_row(g, i) != 0) {
            game_delete(g);
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != EMPTY || game_get_expected_nb_tents_col(g, j) != 0) {
                game_delete(g);
                return false;
            }
    }
    game_delete(g);
    return true;
}

bool test_game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool diagadj)
{
    game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, diagadj);
    if (game_nb_rows(g) != nb_rows)
        return false;
    if (game_nb_cols(g) != nb_cols)
        return false;
    if (game_is_wrapping(g) != wrapping)
        return false;
    if (game_is_diagadj(g) != diagadj)
        return false;
    //Tests, for each square, if the value is EMPTY and if the number of expected tents is 0 for each row and column
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (game_get_expected_nb_tents_row(g, i) != 0) {
            game_delete(g);
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != EMPTY || game_get_expected_nb_tents_col(g, j) != 0) {
                game_delete(g);
                return false;
            }
    }
    game_delete(g);
    return true;
}

bool test_game_copy(square* squares, uint* nb_tents_row, uint* nb_tents_col)
{
    //Creates the game using the arguments as parameters
    game g1 = game_new(squares, nb_tents_row, nb_tents_col);
    game g2 = game_copy(g1);
    /*
    Tests, for each square, if the value is equal between the 2 games and if the number of expected tents 
    is equal between the 2 games for each row and column
    */
    bool assert = game_equal(g1, g2);
    game_delete(g1);
    game_delete(g2);
    return assert;
}

bool test_game_equal(square* squares, uint* nb_tents_row, uint* nb_tents_col)
{
    //Creates the same 3 games using the arguments as parameters
    game g1 = game_new(squares, nb_tents_row, nb_tents_col);
    game g2 = game_new(squares, nb_tents_row, nb_tents_col);
    game g3 = game_new(squares, nb_tents_row, nb_tents_col);
    //Changes the 3rd game in order to make it different from the 2 others
    game_set_expected_nb_tents_col(g3, 0, nb_tents_col[0] + 1);
    bool assert1 = game_equal(g1, g2);
    bool assert2 = !game_equal(g1, g3);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return assert1 && assert2;
}

bool test_game_delete(void)
{
    //Creates an empty game, copies it then deletes the 1st one and checks if the 2 games are different asserting that the 1st one is indeed deleted
    game g = game_default();
    game_delete(g);
    return true;
}

bool test_game_default_solution(void)
{
    //Parameters corresponding to the solution of the default game
    square squares[64] = {
        TENT, GRASS, GRASS, TENT, TREE, TREE, TENT, GRASS,
        TREE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, TREE,
        TENT, GRASS, GRASS, TENT, TREE, TENT, GRASS, TENT,
        TREE, GRASS, GRASS, GRASS, GRASS, TREE, GRASS, GRASS,
        TENT, TREE, TENT, GRASS, TENT, GRASS, TENT, GRASS,
        TREE, GRASS, GRASS, GRASS, TREE, GRASS, TREE, GRASS,
        TENT, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS,
        TREE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS
    };
    uint nb_tents_row[8] = { 3, 0, 4, 0, 4, 0, 1, 0 };
    uint nb_tents_col[8] = { 4, 0, 1, 2, 1, 1, 2, 1 };
    //Asserting that the game_default_solution() is equal to the solution game we created
    game g1 = game_default_solution();
    game g2 = game_new(squares, nb_tents_row, nb_tents_col);
    bool assert = game_equal(g1, g2);
    game_delete(g1);
    game_delete(g2);
    return assert;
}

int main(int argc, char* argv[])
{
    //Parameters used to create the games used in the tests
    square squares[64] = {
        EMPTY, EMPTY, EMPTY, EMPTY, TREE, TREE, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, TREE,
        EMPTY, EMPTY, TREE, EMPTY, TREE, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, TREE, EMPTY, EMPTY,
        EMPTY, TREE, EMPTY, EMPTY, TREE, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, TREE, EMPTY, TREE, EMPTY,
        EMPTY, TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
    };
    uint nb_tents_row[8] = { 3, 5, 4, 0, 4, 2, 1, 0 };
    uint nb_tents_col[8] = { 4, 0, 1, 2, 1, 1, 2, 1 };

    bool ok = false;
    if (strcmp("game_new", argv[1]) == 0)
        ok = test_game_new(squares, nb_tents_row, nb_tents_col);
    else if (strcmp("game_new_ext", argv[1]) == 0)
        ok = test_game_new_ext(squares, nb_tents_row, nb_tents_col, DEFAULT_SIZE, DEFAULT_SIZE, true, false);
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else if (strcmp("game_new_empty_ext", argv[1]) == 0)
        ok = test_game_new_empty_ext(0, 0, false, false);
    else if (strcmp("game_copy", argv[1]) == 0)
        ok = test_game_copy(squares, nb_tents_row, nb_tents_col);
    else if (strcmp("game_equal", argv[1]) == 0)
        ok = test_game_equal(squares, nb_tents_row, nb_tents_col);
    else if (strcmp("game_delete", argv[1]) == 0)
        ok = test_game_delete();
    else if (strcmp("game_default_solution", argv[1]) == 0)
        ok = test_game_default_solution();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}