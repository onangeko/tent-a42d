#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include <stdio.h>
#include <stdlib.h>

char sqrToCharTool(square s)
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

game game_load(char* filename)
{
    return NULL;
}

void game_save(cgame g, char* filename)
{
    if (g == NULL) {
        exit(EXIT_FAILURE);
    }
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        exit(EXIT_FAILURE);
    }
    // first line: <nb_rows> <nb_cols> <is_swap> <is_diagadj>\n
    fprintf(f, "%d %d %d %d\n", game_nb_rows(g), game_nb_cols(g), game_is_wrapping(g), game_is_diagadj(g));
    // second line: <nb_tents_row[0]> <nb_tents_row[1]> ... <nb_tents_row[nb_rows-1]> \n
    for (int i = 0; i < game_nb_rows(g); i++) {
        fprintf(f, "%d ", game_get_expected_nb_tents_row(g, i));
    }
    fprintf(f, "\n");
    // third line: <nb_tents_col[0]> <nb_tents_col[1]> ... <nb_tents_col[nb_cols-1]> \n
    for (int j = 0; j < game_nb_cols(g); j++) {
        fprintf(f, "%d ", game_get_expected_nb_tents_col(g, j));
    }
    fprintf(f, "\n");
    for (int i = 0; i < game_nb_rows(g); i++) {
        for (int j = 0; j < game_nb_cols(g); j++) {
            fprintf(f, "%c ", sqrToCharTool(game_get_square(g, i, j)));
        }
        fprintf(f, "\n");
    }
    fclose(f);
}