#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_aux.h"

bool test_game_new(square *squares, uint *nb_tents_row, uint *nb_tents_col)
{
    //Creates the game using the default game parameters
    game g = game_new(squares, nb_tents_row, nb_tents_col);
    //Tests, for each square, if it is the same as the parameters we put in
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        if (game_get_expected_nb_tents_row(g, i) != nb_tents_row[i])
        {
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != squares[(i * 8) + j] || game_get_expected_nb_tents_col(g, j) != nb_tents_col[j])
                return false;
    }
    return true;
}

bool test_game_new_empty(void)
{
    game g = game_new_empty();
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        if (game_get_expected_nb_tents_row(g, i) != 0)
        {
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != EMPTY || game_get_expected_nb_tents_col(g, j) != 0)
                return false;
    }
    return true;
}

bool test_game_copy(square *squares, uint *nb_tents_row, uint *nb_tents_col)
{
    //Creates the game using the default game parameters
    game g1 = game_new(squares, nb_tents_row, nb_tents_col);
    game g2 = game_copy(g1);
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        if (game_get_expected_nb_tents_row(g1, i) != game_get_expected_nb_tents_row(g2, i))
            return false;
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g1, i, j) != game_get_square(g2, i, j) || game_get_expected_nb_tents_col(g1, j) != game_get_expected_nb_tents_col(g1, j))
                return false;
    }
    return true;
    //TODO
}

bool test_game_equal(square *squares, uint *nb_tents_row, uint *nb_tents_col)
{
    game g1 = game_new(squares, nb_tents_row, nb_tents_col);
    game g2 = game_new(squares, nb_tents_row, nb_tents_col);
    game g3 = game_new(squares, nb_tents_row, nb_tents_col);
    game_set_expected_nb_tents_col(g3, 0, game_get_current_nb_tents_col(g3, 0) + 1);
    return game_equal(g1, g2) && !game_equal(g1, g3);
}

bool test_game_delete(void)
{
    game g1 = game_new_empty();
    game g2 = game_copy(g1);
    game_delete(g1);
    return !game_equal(g1, g2);
}

bool test_game_default(void)
{
    square squares[64] = {
        EMPTY, EMPTY, EMPTY, EMPTY, TREE, TREE, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, TREE,
        EMPTY, EMPTY, EMPTY, EMPTY, TREE, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, TREE, EMPTY, EMPTY,
        EMPTY, TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, TREE, EMPTY, TREE, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    uint nb_tents_row[8] = {3, 0, 4, 0, 4, 0, 1, 0};
    uint nb_tents_col[8] = {4, 0, 1, 2, 1, 1, 2, 1};
    //Creates the game using the default game parameters
    game g = game_default();
    //Tests, for each square, if it is the same as the parameters we put in
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        if (game_get_expected_nb_tents_row(g, i) != nb_tents_row[i])
        {
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (game_get_square(g, i, j) != squares[(i * 8) + j] || game_get_expected_nb_tents_col(g, j) != nb_tents_col[j])
                return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    //Creating the default parameters by hand
    square squares[64] = {
        EMPTY, EMPTY, EMPTY, EMPTY, TREE, TREE, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, TREE,
        EMPTY, EMPTY, TREE, EMPTY, TREE, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, TREE, EMPTY, EMPTY,
        EMPTY, TREE, EMPTY, EMPTY, TREE, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, TREE, EMPTY, TREE, EMPTY,
        EMPTY, TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        TREE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    uint nb_tents_row[8] = {3, 5, 4, 0, 4, 2, 1, 0};
    uint nb_tents_col[8] = {4, 0, 1, 2, 1, 1, 2, 1};

    bool ok = false;
    if (strcmp("game_new", argv[1]) == 0)
        ok = test_game_new(squares, nb_tents_row, nb_tents_col);
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else if (strcmp("game_copy", argv[1]) == 0)
        ok = test_game_copy(squares, nb_tents_row, nb_tents_col);
    else if (strcmp("game_equal", argv[1]) == 0)
        ok = test_game_equal(squares, nb_tents_row, nb_tents_col);
    else if (strcmp("game_delete", argv[1]) == 0)
        ok = test_game_delete();
    else if (strcmp("game_default", argv[1]) == 0)
        ok = test_game_default();
    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}