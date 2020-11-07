#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_aux.h"

/* ********** TEST GET_SQUARE ********** */
bool test_game_get_square(){
    //default game
    game g = game_default();
    //EMPTY square
    square s = game_get_square(g,0,0);
    if(s != EMPTY)
        return false;
    //TREE square
    s = game_get_square(g,0,5);
    if(s != TREE)
        return false;
    //TENT square
    game_set_square(g,0,0,TENT);
    s = game_get_square(g,0,0);
    if(s !=TENT ){
        return false;
    }
    //GRASS square
    game_set_square(g,0,0,GRASS);
    s = game_get_square(g,0,0);
    if(s!=GRASS){
        return false;
    }
    return true;
}

/* ********** TEST SET_SQUARE ********** */
bool test_game_set_square(){
    //default game
    game g = game_default();
    //EMPTY square
    game_set_square(g,0,0,EMPTY);
    square s = game_get_square(g,0,0);
    if(s != EMPTY)
        return false;
    //TENT square
    game_set_square(g,0,0,TENT);
    s = game_get_square(g,0,0);
    if(s !=TENT ){
        return false;
    }
    //GRASS square
    game_set_square(g,0,0,GRASS);
    s = game_get_square(g,0,0);
    if(s!=GRASS){
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    bool ok = false;
    if (strcmp("game_get_square", argv[1]) == 0)
        ok = test_game_get_square();
    else if(strcmp("game_set_square", argv[1]) == 0)
        ok = test_game_set_square();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // print test result
    if (ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
