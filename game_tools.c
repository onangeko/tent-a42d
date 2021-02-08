#include "game.h"
#include "game_ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

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
    }
    //3rd Line
    fgets(str, MAXCHAR, fp);
    uint nb_tents_col[nb_cols];
    for (int i = 0; i < nb_rows; i++) {
        sscanf(str, "%u ", &nb_tents_col[i]);
    }
    square* squares = malloc(sizeof(square) * nb_rows * nb_cols);
    for (uint i = 0; i < nb_rows; i++) {
        fgets(str, MAXCHAR, fp);
        for (uint j = 0; j < nb_cols; j++) {
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
            squares[i * nb_rows + j] = sq;
        }
    }

    fclose(fp);
    return game_new_ext(nb_rows, nb_cols, squares, nb_tents_row, nb_tents_col, wrapping == 1, diagadj == 1);
}

void game_save(cgame g, char* filename)
{
}