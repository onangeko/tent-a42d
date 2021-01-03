#include "game.h"
#include "game_ext.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct game_s {
    // board size
    uint nb_rows;
    uint nb_cols;
    // the board
    square** board;
    uint* expected_nb_tents_col;
    uint* expected_nb_tents_row;
    // options
    bool wrapping;
    bool diagadj;
    // undo / redo
    game previousState;
    game nextState;
} game_s;

game game_new(square* squares, uint* nb_tents_row, uint* nb_tents_col)
{
    if (squares == NULL || nb_tents_row == NULL || nb_tents_col == NULL) {
        exit(EXIT_FAILURE);
    }
    struct game_s* game = malloc(sizeof(struct game_s));
    game->board = malloc(sizeof(square*) * DEFAULT_SIZE);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        game->board[i] = malloc(sizeof(square) * DEFAULT_SIZE);
    }
    game->expected_nb_tents_row = malloc(sizeof(uint) * DEFAULT_SIZE);
    game->expected_nb_tents_col = malloc(sizeof(uint) * DEFAULT_SIZE);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        game->expected_nb_tents_col[i] = nb_tents_col[i];
        game->expected_nb_tents_row[i] = nb_tents_row[i];
    }
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            game->board[i][j] = squares[i * DEFAULT_SIZE + j];
        }
    }
    return game;
}

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, uint* nb_tents_row, uint* nb_tents_col, bool wrapping,
    bool diagadj)
{
    game game = game_new(squares, nb_tents_row, nb_tents_col);
    game->wrapping = wrapping;
    game->diagadj = diagadj;
    game->nb_rows = nb_rows;
    game->nb_cols = nb_cols;
    return game;
}

game game_new_empty(void)
{
    square* squares = (square*)malloc(sizeof(square) * DEFAULT_SIZE * DEFAULT_SIZE);
    for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
        squares[i] = EMPTY;
    }
    uint* nb_tents_row = (uint*)malloc(sizeof(uint) * DEFAULT_SIZE);
    uint* nb_tents_col = (uint*)malloc(sizeof(uint) * DEFAULT_SIZE);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        nb_tents_row[i] = 0;
        nb_tents_col[i] = 0;
    }
    game empty = game_new(squares, nb_tents_row, nb_tents_col);
    free(squares);
    free(nb_tents_col);
    free(nb_tents_row);
    return empty;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool diagadj)
{
    game game = game_new_empty();
    game->wrapping = wrapping;
    game->diagadj = diagadj;
    game->nb_rows = nb_rows;
    game->nb_cols = nb_cols;
    return game;
}

bool game_get_wrapping(game g)
{
    return g->wrapping;
}

bool game_get_diagadj(game g)
{
    return g->diagadj;
}

uint game_get_nb_rows(game g)
{
    return g->nb_rows;
}

uint game_get_nb_cols(game g)
{
    return g->nb_cols;
}

game game_copy(cgame g)
{
    square* squares = malloc(DEFAULT_SIZE * DEFAULT_SIZE * sizeof(square));
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            squares[i * DEFAULT_SIZE + j] = g->board[i][j];
        }
    }
    game copy = game_new_ext(g->nb_rows, g->nb_cols, squares, g->expected_nb_tents_row, g->expected_nb_tents_col, g->wrapping, g->diagadj);
    if (g->previousState != NULL) {
        copy->previousState = g->previousState;
    }
    if (g->nextState != NULL) {
        copy->nextState = g->nextState;
    }
    free(squares);
    return copy;
}

bool game_equal(cgame g1, cgame g2)
{
    if (g1 == NULL || g2 == NULL) {
        return false;
    }
    if (g1->board == NULL || g1->expected_nb_tents_col == NULL || g1->expected_nb_tents_row == NULL || g2->board == NULL || g2->expected_nb_tents_col == NULL || g2->expected_nb_tents_row == NULL) {
        return false;
    }
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (game_get_expected_nb_tents_col(g1, i) != game_get_expected_nb_tents_col(g2, i)
            || game_get_expected_nb_tents_row(g1, i) != game_get_expected_nb_tents_row(g2, i)
            || game_get_current_nb_tents_col(g1, i) != game_get_current_nb_tents_col(g2, i)
            || game_get_current_nb_tents_row(g1, i) != game_get_current_nb_tents_row(g2, i)) {
            return false;
        }
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_square(g1, i, j) != game_get_square(g2, i, j)) {
                return false;
            }
        }
    }
    return true;
}

void game_delete(game g)
{
    if (g != NULL) {
        if (g->previousState != NULL) {
            //Prevents infinite loop
            g->previousState->nextState = NULL;
            game_delete(g->previousState);
        }
        if (g->nextState != NULL) {
            //Prevents infinite loop
            g->nextState->previousState = NULL;
            game_delete(g->nextState);
        }
        if (g->board != NULL) {
            for (int i = 0; i < DEFAULT_SIZE; i++) {
                if (g->board[i] != NULL) {
                    free(g->board[i]);
                    g->board[i] = NULL;
                }
            }
            free(g->board);
            g->board = NULL;
        }
        if (g->expected_nb_tents_col != NULL) {
            free(g->expected_nb_tents_col);
            g->expected_nb_tents_col = NULL;
        }
        if (g->expected_nb_tents_row != NULL) {
            free(g->expected_nb_tents_row);
            g->expected_nb_tents_row = NULL;
        }
        free(g);
        g = NULL;
    }
}

void game_set_square(game g, uint i, uint j, square s)
{
    if (g == NULL || g->board == NULL || i > DEFAULT_SIZE || j > DEFAULT_SIZE) {
        fprintf(stderr, "Error: Invalid argument | game_get_square()");
        exit(EXIT_FAILURE);
    }
    g->board[i][j] = s;
}

square
game_get_square(cgame g, uint i, uint j)
{
    if (g == NULL || g->board == NULL || i > DEFAULT_SIZE || j > DEFAULT_SIZE) {
        fprintf(stderr, "Error: Invalid argument | game_get_square()");
        exit(EXIT_FAILURE);
    }
    return g->board[i][j];
}

/////--BJORN

void game_set_expected_nb_tents_row(game g, uint i, uint nb_tents)
{
    if (g == NULL || i >= DEFAULT_SIZE) {
        printf("invalid arguments");
        exit(0);
    }

    g->expected_nb_tents_row[i] = nb_tents;
}

void game_set_expected_nb_tents_col(game g, uint j, uint nb_tents)
{
    if (g == NULL || j >= DEFAULT_SIZE) {
        printf("invalid arguments");
        exit(0);
    }

    g->expected_nb_tents_col[j] = nb_tents;
}

uint game_get_expected_nb_tents_row(cgame g, uint i)
{
    if (g == NULL || i >= DEFAULT_SIZE) {
        printf("invalid arguments");
        exit(0);
    }

    return g->expected_nb_tents_row[i];
}

uint game_get_expected_nb_tents_col(cgame g, uint j)
{
    if (g == NULL || j >= DEFAULT_SIZE) {
        printf("invalid arguments");
        exit(0);
    }

    return g->expected_nb_tents_col[j];
}

uint game_get_expected_nb_tents_all(cgame g)
{
    if (g == NULL) {
        printf("invalid arguments");
        exit(0);
    }

    unsigned int n = 0;

    for (int i = 0; i < DEFAULT_SIZE; i++)
        n = n + g->expected_nb_tents_row[i];

    return n;
}

/////--

uint game_get_current_nb_tents_row(cgame g, uint i)
{
    if (g == NULL || g->board == NULL || i > DEFAULT_SIZE) {
        fprintf(stderr, "Error: Invalid argument | game_get__expected_nb_tents_row()");
        exit(EXIT_FAILURE);
    }
    uint cpt = 0;
    for (int j = 0; j < DEFAULT_SIZE; j++) {
        if (g->board[i][j] == TENT) {
            cpt = cpt + 1;
        }
    }
    return cpt;
}

uint game_get_current_nb_tents_col(cgame g, uint j)
{
    if (g == NULL || g->board == NULL || j > DEFAULT_SIZE) {
        fprintf(stderr, "Error: Invalid argument | game_get__expected_nb_tents_col()");
        exit(EXIT_FAILURE);
    }
    uint cpt = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (g->board[i][j] == TENT) {
            cpt = cpt + 1;
        }
    }
    return cpt;
}

uint game_get_current_nb_tents_all(cgame g)
{
    if (g == NULL || g->board == NULL) {
        fprintf(stderr, "Error: Invalid argument | game_get_current_nb_tents_all()");
        exit(EXIT_FAILURE);
    }
    uint cpt = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (g->board[i][j] == TENT) {
                cpt = cpt + 1;
            }
        }
    }
    return cpt;
}

void game_play_move(game g, uint i, uint j, square s)
{
    if (g->nextState != NULL) {
        game next = g->nextState;
        next->previousState = NULL;
        game_delete(next);
        g->nextState = NULL;
    }
    game copy = game_copy(g);
    if (g->previousState != NULL)
        g->previousState->nextState = copy;
    g->previousState = copy;
    copy->nextState = g;
    if (s != TREE && game_get_square(g, i, j) != TREE)
        game_set_square(g, i, j, s);
}

int nb_type_square_row(cgame g, uint i, square s)
{
    int nb = 0;
    for (int j = 0; j < DEFAULT_SIZE; j++) {
        if (game_get_square(g, i, j) == s) {
            nb++;
        }
    }
    return nb;
}

uint nb_type_square_col(cgame g, uint j, square s)
{
    uint nb = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (game_get_square(g, i, j) == s) {
            nb++;
        }
    }
    return nb;
}

bool is_adjacent_orthogonally_to(cgame g, uint i, uint j, square s)
{
    if (i > 0) {
        if (game_get_square(g, i - 1, j) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (game_get_square(g, i + DEFAULT_SIZE - 1, j) == s)
            return true;
    }
    if (i < DEFAULT_SIZE - 1) {
        if (game_get_square(g, i + 1, j) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (game_get_square(g, i - DEFAULT_SIZE + 1, j) == s)
            return true;
    }
    if (j > 0) {
        if (game_get_square(g, i, j - 1) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (game_get_square(g, i, j + DEFAULT_SIZE - 1) == s)
            return true;
    }
    if (j < DEFAULT_SIZE - 1) {
        if (game_get_square(g, i, j + 1) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (game_get_square(g, i, j - DEFAULT_SIZE + 1) == s)
            return true;
    }
    return false;
}

bool is_adjacent_diagonaly_to(cgame g, uint i, uint j, square s)
{
    if (i > 0 && j > 0) {
        if (game_get_square(g, i - 1, j - 1) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (i == 0 && j == 0) {
            if (game_get_square(g, i + DEFAULT_SIZE - 1, j + DEFAULT_SIZE - 1) == s)
                return true;
        } else if (i == 0 && j != 0) {
            if (game_get_square(g, i + DEFAULT_SIZE - 1, j - 1) == s)
                return true;
        } else if (i != 0 && j == 0) {
            if (game_get_square(g, i - 1, j + DEFAULT_SIZE - 1) == s)
                return true;
        }
    }
    if (i < DEFAULT_SIZE - 1 && j < DEFAULT_SIZE - 1) {
        if (game_get_square(g, i + 1, j + 1) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (i == DEFAULT_SIZE - 1 && j == DEFAULT_SIZE - 1) {
            if (game_get_square(g, i - DEFAULT_SIZE + 1, j - DEFAULT_SIZE + 1) == s)
                return true;
        } else if (i == DEFAULT_SIZE - 1 && j != DEFAULT_SIZE - 1) {
            if (game_get_square(g, i - DEFAULT_SIZE + 1, j + 1) == s)
                return true;
        } else if (i != DEFAULT_SIZE - 1 && j == DEFAULT_SIZE - 1) {
            if (game_get_square(g, i + 1, j - DEFAULT_SIZE + 1) == s)
                return true;
        }
    }
    if (j > 0 && i < DEFAULT_SIZE - 1) {
        if (game_get_square(g, i + 1, j - 1) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (i == DEFAULT_SIZE - 1 && j == 0) {
            if (game_get_square(g, i - DEFAULT_SIZE + 1, j + DEFAULT_SIZE - 1) == s)
                return true;
        } else if (i == DEFAULT_SIZE - 1 && j != 0) {
            if (game_get_square(g, i - DEFAULT_SIZE + 1, j - 1) == s)
                return true;
        } else if (i != DEFAULT_SIZE - 1 && j == 0) {
            if (game_get_square(g, i + 1, j + DEFAULT_SIZE - 1) == s)
                return true;
        }
    }
    if (j < DEFAULT_SIZE - 1 && i > 0) {
        if (game_get_square(g, i - 1, j + 1) == s)
            return true;
    } else if (game_is_wrapping(g)) {
        if (i == 0 && j == DEFAULT_SIZE - 1) {
            if (game_get_square(g, i + DEFAULT_SIZE - 1, j - DEFAULT_SIZE + 1) == s)
                return true;
        } else if (i == 0 && j != DEFAULT_SIZE - 1) {
            if (game_get_square(g, i + DEFAULT_SIZE - 1, j + 1) == s)
                return true;
        } else if (i != 0 && j == DEFAULT_SIZE - 1) {
            if (game_get_square(g, i - 1, j - DEFAULT_SIZE + 1) == s)
                return true;
        }
    }
    return false;
}

int check_tent_move(cgame g, uint i, uint j)
{
    //Illegal move
    //* plant a tent on a tree
    if (game_get_square(g, i, j) == TREE)
        return ILLEGAL;

    //Losing moves
    //* plant n+1 tents when n tents are expected in the entire board
    if (game_get_current_nb_tents_all(g) >= game_get_expected_nb_tents_all(g))
        return LOSING;
    //* plant tent adjacent to another orthogonally and diagonally
    if (is_adjacent_orthogonally_to(g, i, j, TENT))
        if (!game_is_diagadj(g) && is_adjacent_diagonaly_to(g, i, j, TENT))
            return LOSING;
    //* plant a tent not adjacent to a tree
    if (!is_adjacent_orthogonally_to(g, i, j, TREE))
        return LOSING;
    //* plant n+1 tents when n tents are expected
    if (game_get_current_nb_tents_row(g, i) >= game_get_expected_nb_tents_row(g, i) || game_get_current_nb_tents_col(g, j) >= game_get_expected_nb_tents_col(g, j))
        return LOSING;

    return REGULAR;
}

bool isTreeSurrounded(cgame g, uint iT, uint jT, uint iG, uint jG)
{
    bool isSurrounded = true;
    if (iT > 0 && iT - 1 != iG) {
        if (game_get_square(g, iT - 1, jT) != GRASS && game_get_square(g, iT - 1, jT) != TREE)
            isSurrounded = false;
    } else if (game_is_wrapping(g)) {
        if (iT == 0 && iT + DEFAULT_SIZE - 1 != iG)
            if (game_get_square(g, iT + DEFAULT_SIZE - 1, jT) != GRASS && game_get_square(g, iT + DEFAULT_SIZE - 1, jT) != TREE)
                isSurrounded = false;
    }
    if (iT < DEFAULT_SIZE - 1 && iT + 1 != iG) {
        if (game_get_square(g, iT + 1, jT) != GRASS && game_get_square(g, iT + 1, jT) != TREE)
            isSurrounded = false;
    } else if (game_is_wrapping(g)) {
        if (iT == DEFAULT_SIZE - 1 && iT - DEFAULT_SIZE + 1 != iG)
            if (game_get_square(g, iT - DEFAULT_SIZE + 1, jT) != GRASS && game_get_square(g, iT - DEFAULT_SIZE + 1, jT) != TREE)
                isSurrounded = false;
    }
    if (jT > 0 && jT - 1 != jG) {
        if (game_get_square(g, iT, jT - 1) != GRASS && game_get_square(g, iT, jT - 1) != TREE)
            isSurrounded = false;
    } else if (game_is_wrapping(g)) {
        if (jT == 0 && jT + DEFAULT_SIZE - 1 != jG)
            if (game_get_square(g, iT, jT + DEFAULT_SIZE - 1) != GRASS && game_get_square(g, iT, jT + DEFAULT_SIZE - 1) != TREE)
                isSurrounded = false;
    }
    if (jT < DEFAULT_SIZE - 1 && jT + 1 != jG) {
        if (game_get_square(g, iT, jT + 1) != GRASS && game_get_square(g, iT, jT + 1) != TREE)
            isSurrounded = false;
    } else if (game_is_wrapping(g)) {
        if (jT == DEFAULT_SIZE - 1 && jT - DEFAULT_SIZE + 1 != jG)
            if (game_get_square(g, iT, jT - DEFAULT_SIZE + 1) != GRASS && game_get_square(g, iT, jT - DEFAULT_SIZE + 1) != TREE)
                isSurrounded = false;
    }
    return isSurrounded;
}

bool isGrassSurroundingTree(cgame g, uint i, uint j)
{
    bool isSurrounding = false;
    if (is_adjacent_orthogonally_to(g, i, j, TREE)) {
        if (i > 0) {
            if (game_get_square(g, i - 1, j) == TREE) {
                isSurrounding = isTreeSurrounded(g, i - 1, j, i, j);
                if (isSurrounding)
                    return true;
            }
        } else if (game_is_wrapping(g)) {
            if (game_get_square(g, i + DEFAULT_SIZE - 1, j) == TREE) {
                isSurrounding = isTreeSurrounded(g, i + DEFAULT_SIZE - 1, j, i, j);
                if (isSurrounding)
                    return true;
            }
        }
        if (i < DEFAULT_SIZE - 1) {
            if (game_get_square(g, i + 1, j) == TREE) {
                isSurrounding = isTreeSurrounded(g, i + 1, j, i, j);
                if (isSurrounding)
                    return true;
            }
        } else if (game_is_wrapping(g)) {
            if (game_get_square(g, i - DEFAULT_SIZE + 1, j) == TREE) {
                isSurrounding = isTreeSurrounded(g, i - DEFAULT_SIZE + 1, j, i, j);
                if (isSurrounding)
                    return true;
            }
        }
        if (j > 0) {
            if (game_get_square(g, i, j - 1) == TREE) {
                isSurrounding = isTreeSurrounded(g, i, j - 1, i, j);
                if (isSurrounding)
                    return true;
            }
        } else if (game_is_wrapping(g)) {
            if (game_get_square(g, i, j + DEFAULT_SIZE - 1) == TREE) {
                isSurrounding = isTreeSurrounded(g, i, j + DEFAULT_SIZE - 1, i, j);
                if (isSurrounding)
                    return true;
            }
        }
        if (j < DEFAULT_SIZE - 1) {
            if (game_get_square(g, i, j + 1) == TREE) {
                isSurrounding = isTreeSurrounded(g, i, j + 1, i, j);
                if (isSurrounding)
                    return true;
            }
        } else if (game_is_wrapping(g)) {
            if (game_get_square(g, i, j - DEFAULT_SIZE + 1) == TREE) {
                isSurrounding = isTreeSurrounded(g, i, j - DEFAULT_SIZE + 1, i, j);
                if (isSurrounding)
                    return true;
            }
        }
    }
    return isSurrounding;
}

int check_grass_move(cgame g, uint i, uint j)
{
    //Illegal move
    //* put grass on a tree
    if (game_get_square(g, i, j) == TREE)
        return ILLEGAL;
    //Losing moves
    //* put grass when number of empty squares is not enough to reach the expected number of tents
    if (game_get_expected_nb_tents_row(g, i) >= (game_get_current_nb_tents_row(g, i) + nb_type_square_row(g, i, EMPTY))
        || game_get_expected_nb_tents_col(g, j) >= (game_get_current_nb_tents_col(g, j) + nb_type_square_col(g, j, EMPTY)))
        return LOSING;
    //* surround a tree with grass
    if (isGrassSurroundingTree(g, i, j))
        return LOSING;

    return REGULAR;
}

int check_empty_move(cgame g, uint i, uint j)
{
    //Illegal move
    //* erase square on a tree
    if (game_get_square(g, i, j) == TREE)
        return ILLEGAL;

    return REGULAR;
}

int game_check_move(cgame g, uint i, uint j, square s)
{
    if (g == NULL || g->board == NULL || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE) {
        fprintf(stderr, "Error: Invalid argument | game_check_move()");
        exit(EXIT_FAILURE);
    } else if (s == TREE)
        return ILLEGAL;
    //Tent move
    else if (s == TENT)
        return check_tent_move(g, i, j);
    //Grass move
    else if (s == GRASS)
        return check_grass_move(g, i, j);
    //Empty move
    else if (s == EMPTY)
        return check_empty_move(g, i, j);
    return REGULAR;
}

bool game_is_over(cgame g)
{
    // the game shall be over only if the 4 rules described in the readme are satisfied and if the tents are correctly placed

    if (g == NULL || g->board == NULL) {
        fprintf(stderr, "Error: Invalid argument | game_is_over()");
    }
    if (game_is_diagadj(g) == true) {
        // RULE 1 ) No two tents are adjacent orthogonally.
        for (int i = 0; i < DEFAULT_SIZE; i++)
            for (int j = 0; j < DEFAULT_SIZE; j++)
                if (g->board[i][j] == TENT)
                    if (is_adjacent_orthogonally_to(g, i, j, TENT))
                        return false;
        goto jump;
    }

    // RULE 1 ) No two tents are adjacent, even diagonally.
    for (int i = 0; i < DEFAULT_SIZE; i++)
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (g->board[i][j] == TENT)
                if (is_adjacent_orthogonally_to(g, i, j, TENT) || is_adjacent_diagonaly_to(g, i, j, TENT))
                    return false;

// RULE 2 ) The number of tents in each row, and in each column, matches the expected numbers given around the sides of the grid.
jump:

    for (int i = 0; i < DEFAULT_SIZE; i++)
        if (game_get_current_nb_tents_row(g, i) != game_get_expected_nb_tents_row(g, i))
            return false;

    for (int j = 0; j < DEFAULT_SIZE; j++)
        if (game_get_current_nb_tents_col(g, j) != game_get_expected_nb_tents_col(g, j))
            return false;

    // RULE 3 ) There are exactly as many tents as trees.
    int cpt = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++)
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (g->board[i][j] == TREE)
                cpt = cpt + 1;
    if (cpt != game_get_current_nb_tents_all(g))
        return false;

    // RULE 4 ) Each tent must be orthogonally adjacent (horizontally or vertically, but not diagonally) to at least one tree and vice versa.
    for (int i = 0; i < DEFAULT_SIZE; i++)
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (g->board[i][j] == TENT)
                if (!is_adjacent_orthogonally_to(g, i, j, TREE))
                    return false;

    for (int i = 0; i < DEFAULT_SIZE; i++)
        for (int j = 0; j < DEFAULT_SIZE; j++)
            if (g->board[i][j] == TREE)
                if (!is_adjacent_orthogonally_to(g, i, j, TENT))
                    return false;
    return true;
}

void game_fill_grass_row(game g, uint i)
{
    for (int j = 0; j < DEFAULT_SIZE; j++) {
        if (g->board[i][j] == EMPTY) {
            g->board[i][j] = GRASS;
        }
    }
}

void game_fill_grass_col(game g, uint j)
{
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (g->board[i][j] == EMPTY) {
            g->board[i][j] = GRASS;
        }
    }
}

void game_restart(game g)
{
    if (g == NULL || g->board == NULL) {
        fprintf(stderr, "Error: Invalid argument | game_get_restart()");
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (g->board[i][j] != TREE) {
                g->board[i][j] = EMPTY;
            }
        }
    }
}

/**
 * game_ext.h implementation
*/
uint game_nb_rows(cgame g)
{
    if (g == NULL) {
        printf("invalid arguments");
        exit(0);
    }

    return g->nb_rows;
}

uint game_nb_cols(cgame g)
{
    if (g == NULL) {
        printf("invalid arguments");
        exit(0);
    }

    return g->nb_cols;
}

///

bool game_is_wrapping(cgame g)
{
    return g->wrapping;
}

bool game_is_diagadj(cgame g)
{
    return g->diagadj;
}

void game_undo(game g)
{
    if (g != NULL) {
        if (g->previousState != NULL) {
            g = g->previousState;
        }
    }
}
void game_redo(game g)
{
    if (g != NULL) {
        if (g->nextState != NULL) {
            g = g->nextState;
        }
    }
}
