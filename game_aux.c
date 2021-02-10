#include "game_aux.h"
#include "game_ext.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Turns square state into it character correspondance.
 * @param s the state
 * @return the corresponding character
 */
char sqrToChar(square s)
{
    switch (s) {
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
    printf("   ");
    for (uint j = 0; j < game_nb_cols(g); j++)
        printf("%d", j);
    printf("\n");
    printf("   ");
    for (uint j = 0; j < game_nb_cols(g); j++)
        printf("-");
    printf("\n");
    for (uint i = 0; i < game_nb_rows(g); i++) {
        printf("%d |", i);
        for (int j = 0; j < game_nb_cols(g); j++) {
            square s = game_get_square(g, i, j);
            printf("%c", sqrToChar(s));
        }
        printf("| %d\n", game_get_expected_nb_tents_row(g, i));
    }
    printf("   ");
    for (uint j = 0; j < game_nb_cols(g); j++)
        printf("-");
    printf("\n");
    printf("   ");
    for (uint j = 0; j < game_nb_cols(g); j++) {
        printf("%d", game_get_expected_nb_tents_col(g, j));
    }
    printf("\n");
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
    game_set_square(defaultGame, 0, 4, TREE);
    game_set_square(defaultGame, 0, 5, TREE);
    game_set_expected_nb_tents_row(defaultGame, 0, 3);
    //row 1
    game_set_square(defaultGame, 1, 0, TREE);
    game_set_square(defaultGame, 1, 7, TREE);
    game_set_expected_nb_tents_row(defaultGame, 1, 0);
    //row 2
    game_set_square(defaultGame, 2, 4, TREE);
    game_set_expected_nb_tents_row(defaultGame, 2, 4);
    //row 3
    game_set_square(defaultGame, 3, 0, TREE);
    game_set_square(defaultGame, 3, 5, TREE);
    game_set_expected_nb_tents_row(defaultGame, 3, 0);
    //row 4
    game_set_square(defaultGame, 4, 1, TREE);
    game_set_expected_nb_tents_row(defaultGame, 4, 4);
    //row 5
    game_set_square(defaultGame, 5, 0, TREE);
    game_set_square(defaultGame, 5, 4, TREE);
    game_set_square(defaultGame, 5, 6, TREE);
    game_set_expected_nb_tents_row(defaultGame, 5, 0);
    //row 6
    //No tree
    game_set_expected_nb_tents_row(defaultGame, 6, 1);
    //row 7
    game_set_square(defaultGame, 7, 0, TREE);
    game_set_expected_nb_tents_row(defaultGame, 7, 0);

    //Set expected number of tents for columns
    //column 0
    game_set_expected_nb_tents_col(defaultGame, 0, 4);
    //column 1
    game_set_expected_nb_tents_col(defaultGame, 1, 0);
    //column 2
    game_set_expected_nb_tents_col(defaultGame, 2, 1);
    //column 3
    game_set_expected_nb_tents_col(defaultGame, 3, 2);
    //column 4
    game_set_expected_nb_tents_col(defaultGame, 4, 1);
    //column 5
    game_set_expected_nb_tents_col(defaultGame, 5, 1);
    //column 6
    game_set_expected_nb_tents_col(defaultGame, 6, 2);
    //column 7
    game_set_expected_nb_tents_col(defaultGame, 7, 1);
    return defaultGame;
}

/**
 * Returns a default solution according to the original default game on the website.
 * @return the default game solution
 */
game game_default_solution(void)
{
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
    return game_new(squares, nb_tents_row, nb_tents_col);
}