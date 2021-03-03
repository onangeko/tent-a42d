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
        printf("file %s not opened properly/not found", filename);
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

bool game_solve_aux(game g, uint row, uint col)
{

    int i = col == game_nb_cols(g) - 1 && row < game_nb_rows(g) ? row + 1 : row;
    int j = col == game_nb_cols(g) - 1 ? 0 : col + 1;
    int remaining_tents_on_row = game_get_expected_nb_tents_row(g, row) - game_get_current_nb_tents_row(g, row);

    //If the game is over then a solution has been found
    if (game_is_over(g))
        return true;

    //If the remaining amount of tents we have to place is more than what we can physically place then the game
    // is not viable and we return false (we multiply it by 2 because two tents cannot be placed next to eachother)
    //For example : If there is 3 tents left to place on a specific row in a 8x8 game and we are already at column number 4
    //then we cannot possibly place 3 tents in 4 squares because one tent has to be next to another so we say that the game
    //is not viable by returning false
    if (game_nb_cols(g) - col + 1 < remaining_tents_on_row * 2) {
        return false;
    }

    //If the precendent row doesn't have the required amount of tents then the game is not viable and we return false
    if (col == 0 && row != 0 && game_get_current_nb_tents_row(g, row - 1) != game_get_expected_nb_tents_row(g, row - 1)) {
        return false;
    }
    //If we reach the end of the board and the game is not over then we return false
    if (row == game_nb_rows(g) - 1 && col == game_nb_cols(g) - 1 && !game_is_over(g)) {
        return false;
    }

    if (game_check_move(g, row, col, TENT) == REGULAR) {
        game_play_move(g, row, col, TENT);
        //system("clear");
        //game_print(g);
        //sleep(0.1);
        if (game_solve_aux(g, i, j)) {
            return true;
        } else {
            game_undo(g);
        }
    }
    return game_solve_aux(g, i, j);
}

bool game_solve(game g)
{
    return game_solve_aux(g, 0, 0);
}

uint game_nb_solutions(game g)
{
    return 0;
}