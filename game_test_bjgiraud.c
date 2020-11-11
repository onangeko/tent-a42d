#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game_aux.h"


void test_game_get_expected_nb_tents_row(game g)
{
    assert((game_get_expected_nb_tents_row(g,0)) == 3);
    assert((game_get_expected_nb_tents_row(g,1)) == 0);
    assert((game_get_expected_nb_tents_row(g,2)) == 4);
    assert((game_get_expected_nb_tents_row(g,3)) == 0);
    assert((game_get_expected_nb_tents_row(g,4)) == 4);
    assert((game_get_expected_nb_tents_row(g,5)) == 0);
    assert((game_get_expected_nb_tents_row(g,6)) == 1);
    assert((game_get_expected_nb_tents_row(g,7)) == 0);
}

///

void test_game_get_expected_nb_tents_all(game g)
{
    assert(game_get_expected_nb_tents_all(g) == 12);
}

///

void test_game_get_expected_nb_tents_col(game g)
{
    assert((game_get_expected_nb_tents_col(g,0)) == 4);
    assert((game_get_expected_nb_tents_col(g,1)) == 0);
    assert((game_get_expected_nb_tents_col(g,2)) == 1);
    assert((game_get_expected_nb_tents_col(g,3)) == 2);
    assert((game_get_expected_nb_tents_col(g,4)) == 1);
    assert((game_get_expected_nb_tents_col(g,5)) == 1);
    assert((game_get_expected_nb_tents_col(g,6)) == 2);
    assert((game_get_expected_nb_tents_col(g,7)) == 1);
}

///////

void test_game_set_expected_nb_tents_row(game g)
{
    game_set_expected_nb_tents_row(g, 0, 3);

    assert(game_get_expected_nb_tents_row(g,0) == 3);


}

///

void test_game_set_expected_nb_tents_col(game g)
{
    game_set_expected_nb_tents_col(g, 0, 4);

    assert(game_get_expected_nb_tents_col(g,0) == 4);


}

///////

    void test_game_default(game g)
{
    for (int i = 0 ; i < 8 ; i++)
        for (int j = 0 ; j < 8 ; j++)
        {

    if (i == 0 && j == 4)
        assert(game_get_square(g,0,4) == TREE);
    else if (i == 0 && j == 5)
        assert(game_get_square(g,0,5) == TREE);
    //row 1
    else if (i == 1 && j == 0)
        assert(game_get_square(g,1,0) == TREE);
    else if (i == 1 && j == 7)
        assert(game_get_square(g,1,7) == TREE);
    //row 2
    else if (i == 2 && j == 4)
        assert(game_get_square(g,2,4) == TREE);
    //row 3
    else if (i == 3 && j == 0)
        assert(game_get_square(g,3,0) == TREE);
    else if (i == 3 && j == 5)
        assert(game_get_square(g,3,5) == TREE);
    //row 4
    else if (i == 4 && j == 1)
        assert(game_get_square(g,4,1) == TREE);
    //row 5
    else if (i == 5 && j == 0)
        assert(game_get_square(g,5,0) == TREE);
    else if (i == 5 && j == 4)
        assert(game_get_square(g,5,4) == TREE);
    else if (i == 5 && j == 6)
        assert(game_get_square(g,5,6) == TREE);
    //row 6
    //No tree
    //row 7
    else if (i == 7 && j == 0)
        assert(game_get_square(g,7,0) == TREE);

    else
    {
        assert(game_get_square(g,i,j) == EMPTY);
    }}}





int main(int argc, char* argv[]){

    game g1 = game_default();

    if (strcmp("game_get_expected_nb_tents_row", argv[1]) == 0)
    {
        test_game_get_expected_nb_tents_row(g1);
    }
    if (strcmp("game_get_expected_nb_tents_all", argv[1]) == 0)
    {
        test_game_get_expected_nb_tents_all(g1);
    }
    if (strcmp("game_get_expected_nb_tents_col", argv[1]) == 0)
    {
        test_game_get_expected_nb_tents_col(g1);
    }
    
    if (strcmp("game_set_expected_nb_tents_row", argv[1]) == 0)
    {
        test_game_set_expected_nb_tents_row(g1);
    }
    if (strcmp("game_set_expected_nb_tents_col", argv[1]) == 0)
    {
        test_game_set_expected_nb_tents_col(g1);
    }

    if (strcmp("game_default", argv[1]) == 0)
    {
        test_game_default(g1);
    }
   

    
    return EXIT_SUCCESS;

}