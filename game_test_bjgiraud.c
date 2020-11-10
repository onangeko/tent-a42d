#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"


int test_game_get_expected_nb_tents_row(game g)
{
    if((game_get_expected_nb_tents_row(g,0)) == 3)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

///

int test_game_get_expected_nb_tents_all(game g)
{
    if(game_get_expected_nb_tents_all(g) == 12)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

///

int test_game_get_expected_nb_tents_col(game g)
{
    if(game_get_expected_nb_tents_col(g,0) == 4)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

///////

int test_game_set_expected_nb_tents_row(game g)
{
    game_set_expected_nb_tents_row(g, 0, 3);

    if(game_get_expected_nb_tents_row(g,0) == 3)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;


}

///

int test_game_set_expected_nb_tents_col(game g)
{
    game_set_expected_nb_tents_col(g, 0, 4);

    if(game_get_expected_nb_tents_col(g,0) == 4)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;


}

///////

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
    
    

}