/**
 * @file game_ext.c
 * @copyright University of Bordeaux. All rights reserved, 2020.
 *
 **/

#include "game_ext.h"
#include "game.h"
#include "game_aux.h"
#include "game_private.h"
#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************** */
/*                                 GAME EXT                                   */
/* ************************************************************************** */

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, uint* nb_tents_row, uint* nb_tents_col, bool wrapping,
    bool diagadj)
{
    game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, diagadj);
    assert(g);
    // set squares
    for (uint i = 0; i < g->nb_rows; i++)
        for (uint j = 0; j < g->nb_cols; j++) {
            square s = squares[i * nb_cols + j];
            assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);
            SQUARE(g, i, j) = s;
        }
    // set expected nb tents in each col
    for (uint j = 0; j < g->nb_cols; j++) {
        assert(nb_tents_col[j] < g->nb_cols);
        g->nb_tents_col[j] = nb_tents_col[j];
    }
    // set expected nb tents in each row
    for (uint i = 0; i < g->nb_rows; i++) {
        assert(nb_tents_row[i] < g->nb_rows);
        g->nb_tents_row[i] = nb_tents_row[i];
    }
    return g;
}

/* ************************************************************************** */

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool diagadj)
{
    game g = (game)malloc(sizeof(struct game_s));
    assert(g);
    g->nb_rows = nb_rows;
    g->nb_cols = nb_cols;
    g->wrapping = wrapping;
    g->diagadj = diagadj;
    g->squares = (square*)calloc(g->nb_rows * g->nb_cols, sizeof(uint)); // EMPTY=0
    assert(g->squares);
    g->nb_tents_col = (uint*)calloc(g->nb_cols, sizeof(uint));
    assert(g->nb_tents_col);
    g->nb_tents_row = (uint*)calloc(g->nb_rows, sizeof(uint));
    assert(g->nb_tents_row);

    // initialize history
    g->undo_stack = queue_new();
    assert(g->undo_stack);
    g->redo_stack = queue_new();
    assert(g->redo_stack);
    return g;
}

/* ************************************************************************** */

uint game_nb_rows(cgame g) { return g->nb_rows; }

/* ************************************************************************** */

uint game_nb_cols(cgame g) { return g->nb_cols; }

/* ************************************************************************** */

bool game_is_wrapping(cgame g) { return g->wrapping; }

/* ************************************************************************** */

bool game_is_diagadj(cgame g) { return g->diagadj; }

/* ************************************************************************** */

void game_undo(game g)
{
    assert(g);
    if (_stack_is_empty(g->undo_stack))
        return;
    move m = _stack_pop_move(g->undo_stack);
    game_set_square(g, m.i, m.j, m.old);
    _stack_push_move(g->redo_stack, m);
}

/* ************************************************************************** */

void game_redo(game g)
{
    assert(g);
    if (_stack_is_empty(g->redo_stack))
        return;
    move m = _stack_pop_move(g->redo_stack);
    game_set_square(g, m.i, m.j, m.new);
    _stack_push_move(g->undo_stack, m);
}

/* ************************************************************************** */
