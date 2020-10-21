#include <stdio.h>
#include <stdlib.h>
#include "game_aux.h"

/**
 * Turns square state into it character correspondance.
 * @param s the state
 * @return the corresponding character
 */
char sqrToChar(square s){
    switch(s){
        case EMPTY:
            return ' ';
        case TREE:
            return 'x';
        case TENT:
            return '*';
        case GRASS:
            return '-';
    }
    return '0';
}

/**
 * Prints the game state in the terminal.
 * @param g the game state
 */
void game_print(cgame g)
{
    printf("   01234567\n");
    printf("   --------\n");
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        printf("%d |",i);
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            square s = game_get_square(g,i,j);
            printf("%c",sqrToChar(s));
        }
        printf("| %d\n",game_get_expected_nb_tents_row(g,i));
    }
    printf("   --------\n");
    printf("   ");
    for(int i=0;i<DEFAULT_SIZE;i++){
        printf("%d",game_get_expected_nb_tents_col(g,i));
    }
    printf("\n\n");
}

/**
 * Returns a default game according to the original game on the website.
 * @return the default game
 */
game game_default(void)
{
    game defaultGame = game_new_empty();
    //Plant trees and set expected number of tents for rows
    //row 0
    game_set_square(defaultGame,0,4,TREE);
    game_set_square(defaultGame,0,5,TREE);
    game_set_expected_nb_tents_row(defaultGame,0,3);
    //row 1
    game_set_square(defaultGame,1,0,TREE);
    game_set_square(defaultGame,1,7,TREE);
    game_set_expected_nb_tents_row(defaultGame,1,0);
    //row 2
    game_set_square(defaultGame,2,4,TREE);
    game_set_expected_nb_tents_row(defaultGame,2,4);
    //row 3
    game_set_square(defaultGame,3,0,TREE);
    game_set_square(defaultGame,3,5,TREE);
    game_set_expected_nb_tents_row(defaultGame,3,0);
    //row 4
    game_set_square(defaultGame,4,1,TREE);
    game_set_expected_nb_tents_row(defaultGame,4,4);
    //row 5
    game_set_square(defaultGame,5,0,TREE);
    game_set_square(defaultGame,5,4,TREE);
    game_set_square(defaultGame,5,6,TREE);
    game_set_expected_nb_tents_row(defaultGame,5,0);
    //row 6
    //No tree
    game_set_expected_nb_tents_row(defaultGame,6,1);
    //row 7
    game_set_square(defaultGame,7,0,TREE);
    game_set_expected_nb_tents_row(defaultGame,7,0);
    
    //Set expected number of tents for columns
    //column 0
    game_set_expected_nb_tents_col(defaultGame,0,4);
    //column 1
    game_set_expected_nb_tents_col(defaultGame,1,0);
    //column 2
    game_set_expected_nb_tents_col(defaultGame,2,1);
    //column 3
    game_set_expected_nb_tents_col(defaultGame,3,2);
    //column 4
    game_set_expected_nb_tents_col(defaultGame,4,1);
    //column 5
    game_set_expected_nb_tents_col(defaultGame,5,1);
    //column 6
    game_set_expected_nb_tents_col(defaultGame,6,2);
    //column 7
    game_set_expected_nb_tents_col(defaultGame,7,1);
    return defaultGame;
}

/**
 * Returns a default solution according to the original default game on the website.
 * @return the default game solution
 */
game game_default_solution(void)
{
    game defaultSolution = game_default();
    //Plant tents and grass by rows
    //row 0
    //Tents
    game_set_square(defaultSolution,0,0,TENT);
    game_set_square(defaultSolution,0,3,TENT);
    game_set_square(defaultSolution,0,6,TENT);
    //Grass
    game_set_square(defaultSolution,0,1,GRASS);
    game_set_square(defaultSolution,0,2,GRASS);
    game_set_square(defaultSolution,0,7,GRASS);
    //row 1
    //No tent
    //Grass
    for(int i = 1;i<7;i++){
        game_set_square(defaultSolution,1,i,GRASS);
    }
    //row 2
    //Tents
    game_set_square(defaultSolution,2,0,TENT);
    game_set_square(defaultSolution,2,3,TENT);
    game_set_square(defaultSolution,2,5,TENT);
    game_set_square(defaultSolution,2,7,TENT);
    //Grass
    game_set_square(defaultSolution,2,1,GRASS);
    game_set_square(defaultSolution,2,2,GRASS);
    game_set_square(defaultSolution,2,6,GRASS);
    //row 3
    //No tent
    //Grass
    for(int i = 1;i<5;i++){
        game_set_square(defaultSolution,3,i,GRASS);
    }
    game_set_square(defaultSolution,3,6,GRASS);
    game_set_square(defaultSolution,3,7,GRASS);
    //row 4
    //Tents
    for(int i = 0;i<7;i+=2){
        game_set_square(defaultSolution,4,i,TENT);
    }
    //Grass
    for(int i = 3;i<8;i+=2){
        game_set_square(defaultSolution,4,i,GRASS);
    }
    //row 5
    //No tent
    //Grass
    game_set_square(defaultSolution,5,1,GRASS);
    game_set_square(defaultSolution,5,2,GRASS);
    game_set_square(defaultSolution,5,3,GRASS);
    game_set_square(defaultSolution,5,5,GRASS);
    game_set_square(defaultSolution,5,7,GRASS);
    //row 6
    //Tent
    game_set_square(defaultSolution,6,0,TENT);
    //Grass
    for (int i = 1; i < 8; i++)
    {
        game_set_square(defaultSolution,6,i,GRASS);
    }
    //row 7
    //No tent
    //Grass
    for (int i = 1; i < 8; i++)
    {
        game_set_square(defaultSolution,7,i,GRASS);
    }
    return defaultSolution;
}