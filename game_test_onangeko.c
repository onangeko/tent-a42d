#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"




int
test_game_is_over()
{
   return EXIT_SUCCESS;

}


int
test_game_restart()
{
    game g1 = game_default();
    game_play_move(g1, 0,0, TENT);
    game_play_move(g1,7,7,GRASS);
    game_restart(g1);

    if (game_get_current_nb_tents_all(g1) == 0 && game_get_square(g1,7,7) == EMPTY)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
 

int test_game_get_current_nb_tents_all ()
{
    game g1 = game_default();
    game_play_move(g1, 0,0, TENT);

    if (game_get_current_nb_tents_all(g1) == 1)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}


/* ********** TEST GAME_CURRENT_NB_TENTS_ROW ********** */

int test_game_get_current_nb_tents_row ()
{
    //default game 
    game g1 = game_default_solution();

    // square(0,0) , square (0,3) and square(0,6) are TENTS in the first row of the default game

    if( (game_get_square(g1,0,0) == TENT)  &&  (game_get_square(g1,0,3) == TENT) && (game_get_square(g1,0,6) == TENT) && (game_get_current_nb_tents_row(g1,0) == 3))
    {
        return EXIT_SUCCESS;
    }
    else 
    {
        return EXIT_FAILURE;
    }
    

}

int test_game_get_current_nb_tents_col ()
{
    //default game 
    game g1 = game_default_solution();
    // square(0,0) , square (2,0),square(4,0) and square(6,0),are TENTS in the first row of the default game
    if( (game_get_square(g1,0,0) == TENT)  &&  (game_get_square(g1,2,0) == TENT) && (game_get_square(g1,4,0) == TENT) && (game_get_square(g1,6,0) == TENT) && (game_get_current_nb_tents_col(g1,0) == 4))
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}

int test_game_print()
{
    game g1 = game_default();
    game_print(g1);
    return EXIT_SUCCESS;
}

int
main(int argc, char *argv[])    
{
      

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    if (strcmp("game_is_over", argv[1]) == 0)
    {
        return test_game_is_over();
    }
    if (strcmp("game_restart", argv[1]) == 0)
    {
        return test_game_restart();
    } 
    if (strcmp("game_current_tents_all", argv[1]) == 0)
    {
        return test_game_get_current_nb_tents_all();
    }
    if (strcmp("game_current_tents_row", argv[1]) == 0)
    {
        return test_game_get_current_nb_tents_row();
    }
    if (strcmp("game_current_tents_col", argv[1]) == 0)
    {
        return test_game_get_current_nb_tents_col();
    } 
    if (strcmp("game_print", argv[1]) == 0)
    {
        return test_game_print();
    } 

}
