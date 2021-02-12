#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

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
    char* str = malloc(sizeof(char) * MAXCHAR);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    //1st Line
    fgets(str, MAXCHAR, fp);
    int nb_rows, nb_cols, wrapping, diagadj;
    sscanf(str, "%d %d %d %d", &nb_rows, &nb_cols, &wrapping, &diagadj);
    //2nd Line
    fgets(str, MAXCHAR, fp);
    uint nb_tents_row[nb_rows];
    for (int i = 0; i < nb_rows; i++) {
        sscanf(str, "%u ", &nb_tents_row[i]);
        str += 2;
    }
    str -= nb_rows * 2;
    //3rd Line
    fgets(str, MAXCHAR, fp);
    uint nb_tents_col[nb_cols];
    for (int i = 0; i < nb_cols; i++) {
        sscanf(str, "%u ", &nb_tents_col[i]);
        str += 2;
    }
    str -= nb_cols * 2;
    //The board
    square* squares = malloc(sizeof(square) * nb_rows * nb_cols);
    for (uint i = 0; i < nb_rows; i++) {
        fgets(str, MAXCHAR, fp);
        for (uint j = 0; j < nb_cols; j++) {
            char charSquare;
            sscanf(str, "%c", &charSquare);
            square sq;
            switch (str[j]) {
            case 'x':
                sq = TREE;
                break;
            case '-':
                sq = GRASS;
                break;
            case ' ':
                sq = EMPTY;
                break;
            case '*':
                sq = TENT;
                break;
            }
            squares[i * nb_cols + j] = sq;
        }
    }

    game game = game_new_ext(nb_rows, nb_cols, squares, nb_tents_row, nb_tents_col, wrapping == 1, diagadj == 1);
    fclose(fp);
    free(str);
    free(squares);
    return game;
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
            fprintf(f, "%c", sqrToCharTool(game_get_square(g, i, j)));
        }
        fprintf(f, "\n");
    }
    fclose(f);
}