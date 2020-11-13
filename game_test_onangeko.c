#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"




int
test_game_is_over()
{
    square squares[64] = {
        TENT, GRASS, GRASS, TENT, TREE, TREE, TENT, GRASS,
        TREE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, TREE,
        TENT, GRASS, GRASS, TENT, TREE, TENT, GRASS, TENT,
        TREE, GRASS, GRASS, GRASS, GRASS, TREE, GRASS, GRASS,
        TENT, TREE, TENT, GRASS, TENT, GRASS, TENT, GRASS,
        TREE, GRASS, GRASS, GRASS, TREE, GRASS, TREE, GRASS,
        TENT, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS,
        TREE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS};

    uint nb_tents_row[8] = {3, 0, 4, 0, 4, 0, 1, 0};
    uint nb_tents_col[8] = {4, 0, 1, 2, 1, 1, 2, 1};
 
    game g1 = game_default_solution();
    game g2 = game_new(squares,nb_tents_row,nb_tents_col);

    if (game_is_over(g2) == true && game_equal(g1,g2) == true)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    } 
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




int test_game_get_current_nb_tents_row ()
{

    game g1 = game_default();
    game_play_move(g1, 0,0, TENT);

    if (game_get_current_nb_tents_row(g1,0) == 1 ) 
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}

int test_game_get_current_nb_tents_col ()
{

    game g1 = game_default();
    game_play_move(g1, 0,0, TENT);

    if (game_get_current_nb_tents_col(g1,0) == 1) 
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
