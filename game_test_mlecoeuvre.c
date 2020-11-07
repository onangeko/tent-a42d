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

/* ********** TEST FILL_GRASS_ROW ********** */
bool test_game_fill_grass_row(){
    //default game
    game g = game_default();
    // fill [0] row with grass
    game_fill_grass_row(g,0);
    for(int i = 0;i<DEFAULT_SIZE;i++){
        // square(0,4) and square(0,5) are trees in default game
        if(i!=4 && i!=5 && game_get_square(g,0,i) != GRASS){
            return false;
        }
    }
    return true;
}

/* ********** TEST FILL_GRASS_COL ********** */
bool test_game_fill_grass_col(){
    //default game
    game g = game_default();
    // fill [0] col with grass
    game_fill_grass_col(g,0);
    for(int i = 0;i<DEFAULT_SIZE;i++){
        // square(1,0) and square(3,0) and square(5,0) and square(7,0) are trees in default game
        if(i!=1 && i!=3 && i!=5 && i!=7 && game_get_square(g,i,0) != GRASS){
            return false;
        }
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
    else if(strcmp("game_fill_grass_row", argv[1]) == 0)
        ok = test_game_fill_grass_row();
    else if(strcmp("game_fill_grass_col", argv[1]) == 0)
        ok = test_game_fill_grass_col();
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
