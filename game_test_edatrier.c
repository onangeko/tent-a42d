#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_aux.h"

bool test_game_new(void)
{
    //Creating the default game by hand
    square *squares = {
        0, 0, 0, 0, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 0, 0, 1, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0};
    uint *nb_tents_row = {1, 0, 4, 0, 4, 0, 1, 0};
    uint *nb_tents_col = {4, 0, 1, 2, 1, 1, 2, 1};
    //Creates the game using the default game parameters
    game g = game_new(squares, nb_tents_row, nb_tents_col);
    //Tests, for each square, if it is the same as the parameters we put in
    for (int i = 0; i < 8; i++)
    {
        if (game_get_current_nb_tents_row(g, i) != nb_tents_row[i])
            return false;
        for (int j = 0; j < 8; j++)
        {
            if (game_get_square(g, i, j) != squares[j * 8 + i] || game_get_current_nb_tents_col(g, j) != nb_tents_col[j])
                return false;
        }
    }
    return true;
}

bool test_game_new_empty(void)
{
    return true;
    //TODO
}

bool test_game_copy(void)
{
    return true;
    //TODO
}

bool test_game_equal(void)
{
    return true;
    //TODO
}

bool test_game_delete(void)
{
    return true;
    //TODO
}

int main(int argc, char *argv[])
{
    return test_game_new();
}