/**
 * @file game.c
 * @copyright University of Bordeaux. All rights reserved, 2020.
 *
 **/

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_private.h"
#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************** */
/*                                 GAME BASIC                                 */
/* ************************************************************************** */

game game_new(square *squares, uint *nb_tents_row, uint *nb_tents_col) {
  return game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, squares, nb_tents_row, nb_tents_col, false, false);
}

/* ************************************************************************** */

game game_new_empty(void) { return game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false); }

/* ************************************************************************** */

game game_copy(cgame g) {
  game gg = game_new_ext(g->nb_rows, g->nb_cols, g->squares, g->nb_tents_row, g->nb_tents_col, g->wrapping, g->diagadj);
  return gg;
}

/* ************************************************************************** */

bool game_equal(cgame g1, cgame g2) {
  assert(g1 && g2);

  if (g1->nb_rows != g2->nb_rows) return false;
  if (g1->nb_cols != g2->nb_cols) return false;

  for (uint i = 0; i < g1->nb_rows; i++) {
    if (g1->nb_tents_row[i] != g2->nb_tents_row[i]) return false;
  }

  for (uint j = 0; j < g1->nb_cols; j++) {
    if (g1->nb_tents_col[j] != g2->nb_tents_col[j]) return false;
  }

  for (uint i = 0; i < g1->nb_rows; i++)
    for (uint j = 0; j < g1->nb_cols; j++) {
      if (SQUARE(g1, i, j) != SQUARE(g2, i, j)) return false;
    }

  if (g1->wrapping != g2->wrapping) return false;
  if (g1->diagadj != g2->diagadj) return false;

  return true;
}

/* ************************************************************************** */

void game_delete(game g) {
  free(g->squares);
  free(g->nb_tents_col);
  free(g->nb_tents_row);
  queue_free_full(g->undo_stack, free);
  queue_free_full(g->redo_stack, free);
  free(g);
}

/* ************************************************************************** */

void game_set_square(game g, uint i, uint j, square s) {
  assert(g);
  assert(i < g->nb_rows);
  assert(j < g->nb_cols);
  assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);
  SQUARE(g, i, j) = s;
}

/* ************************************************************************** */

square game_get_square(cgame g, uint i, uint j) {
  assert(g);
  assert(i < g->nb_rows);
  assert(j < g->nb_cols);
  return SQUARE(g, i, j);
}

/* ************************************************************************** */

void game_set_expected_nb_tents_row(game g, uint i, uint nb_tents) {
  assert(g);
  assert(i < g->nb_rows);
  g->nb_tents_row[i] = nb_tents;
}

/* ************************************************************************** */

void game_set_expected_nb_tents_col(game g, uint j, uint nb_tents) {
  assert(g);
  assert(j < g->nb_cols);
  g->nb_tents_col[j] = nb_tents;
}

/* ************************************************************************** */

uint game_get_expected_nb_tents_row(cgame g, uint i) {
  assert(g);
  assert(i < g->nb_rows);
  return g->nb_tents_row[i];
}

/* ************************************************************************** */

uint game_get_expected_nb_tents_col(cgame g, uint j) {
  assert(g);
  assert(j < g->nb_cols);
  return g->nb_tents_col[j];
}

/* ************************************************************************** */

uint game_get_expected_nb_tents_all(cgame g) {
  assert(g);
  return _nb_squares(g, TREE);
}

/* ************************************************************************** */

uint game_get_current_nb_tents_row(cgame g, uint i) {
  assert(g);
  assert(i < g->nb_rows);
  return _nb_squares_row(g, i, TENT);
}

/* ************************************************************************** */

uint game_get_current_nb_tents_col(cgame g, uint j) {
  assert(g);
  assert(j < g->nb_cols);
  return _nb_squares_col(g, j, TENT);
}

/* ************************************************************************** */

uint game_get_current_nb_tents_all(cgame g) {
  assert(g);
  return _nb_squares(g, TENT);
}

/* ************************************************************************** */

void game_play_move(game g, uint i, uint j, square s) {
  assert(g);
  assert(i < g->nb_rows);
  assert(j < g->nb_cols);
  assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);
  assert(s != TREE);
  square ss = SQUARE(g, i, j);
  assert(ss != TREE);
  SQUARE(g, i, j) = s;

  // save history
  _stack_clear(g->redo_stack);
  move m = {i, j, ss, s};
  _stack_push_move(g->undo_stack, m);
}

/* ************************************************************************** */

int game_check_move(cgame g, uint i, uint j, square s) {
  assert(g);
  assert(i < g->nb_rows);
  assert(j < g->nb_cols);
  assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);
  square cs = SQUARE(g, i, j);  // current square at direction (i,j)

  // === check rule 0 === //

  if (s == TREE) return ILLEGAL;
  if (cs == TREE) return ILLEGAL;

  // No need to check rules, if I play an EMPTY move!
  if (s == EMPTY) return REGULAR;

  // Nota Bene: starting from this line, s is either TENT or GRASS.

  // update nb empty & tent squares, after playig move s
  int delta_empty_squares = ((s == EMPTY) ? 1 : 0) - ((cs == EMPTY) ? 1 : 0);
  int nb_empty_squares_row = _nb_squares_row(g, i, EMPTY) + delta_empty_squares;
  int nb_empty_squares_col = _nb_squares_col(g, j, EMPTY) + delta_empty_squares;
  int nb_empty_squares_all = _nb_squares(g, EMPTY) + delta_empty_squares;
  int delta_tent_squares = ((s == TENT) ? 1 : 0) - ((cs == TENT) ? 1 : 0);
  int nb_tent_squares_row = _nb_squares_row(g, i, TENT) + delta_tent_squares;
  int nb_tent_squares_col = _nb_squares_col(g, j, TENT) + delta_tent_squares;
  int nb_tent_squares_all = _nb_squares(g, TENT) + delta_tent_squares;
  int delta_grass_squares = ((s == GRASS) ? 1 : 0) - ((cs == GRASS) ? 1 : 0);
  // int nb_grass_squares_row = _nb_squares_row(g, i, GRASS) + delta_grass_squares;
  // int nb_grass_squares_col = _nb_squares_col(g, j, GRASS) + delta_grass_squares;
  // int nb_grass_squares_all = _nb_squares(g, GRASS) + delta_grass_squares;

  // === check rule 1 === //

  // no two tents are adjacent, even diagonally
  if ((s == TENT) && _neigh(g, i, j, TENT, !g->diagadj)) return LOSING;

  // === check rule 2 === //

  // 2.1) too much tents in a row or col
  // just check this rule, if I play TENT
  if (s == TENT) {
    if (nb_tent_squares_row > g->nb_tents_row[i]) return LOSING;
    if (nb_tent_squares_col > g->nb_tents_col[j]) return LOSING;
  }

  // 2.2) not enough empty squares in a row or col
  // just check this rule, if I play GRASS
  if (s == GRASS) {
    if ((nb_empty_squares_row + nb_tent_squares_row) < g->nb_tents_row[i]) return LOSING;
    if ((nb_empty_squares_col + nb_tent_squares_col) < g->nb_tents_col[j]) return LOSING;
  }

  // === check rule 3 === //

  // 3.1) too much tents
  // just check this rule, if I play TENT
  if (s == TENT) {
    if (nb_tent_squares_all > _nb_squares(g, TREE)) return LOSING;
  }

  // 3.2) not enough empty squares to place all tents
  // just check this rule, if I play GRASS
  if (s == GRASS) {
    if ((nb_empty_squares_all + nb_tent_squares_all) < _nb_squares(g, TREE)) return LOSING;
  }

  // === check rule 4 === //

  // 4.1) each tent must be orthogonally adjacent to at least one tree.
  if ((s == TENT) && !_neigh(g, i, j, TREE, false)) return LOSING;

  // 4.2) each tree must be orthogonally adjacent to at least one tent.

  // So, if I play grass, it should not prevent an adjacent tree to have at
  // least a tent in its neighborhood...
  if (s == GRASS) {
    if (_test_neigh(g, i, j, TREE, UP) &&
        ((_neigh_count(g, i - 1, j, GRASS, false) + delta_grass_squares) == _neigh_size(g, i - 1, j, false)))
      return LOSING;
    if (_test_neigh(g, i, j, TREE, DOWN) &&
        ((_neigh_count(g, i + 1, j, GRASS, false) + delta_grass_squares) == _neigh_size(g, i + 1, j, false)))
      return LOSING;
    if (_test_neigh(g, i, j, TREE, LEFT) &&
        ((_neigh_count(g, i, j - 1, GRASS, false) + delta_grass_squares) == _neigh_size(g, i, j - 1, false)))
      return LOSING;
    if (_test_neigh(g, i, j, TREE, RIGHT) &&
        ((_neigh_count(g, i, j + 1, GRASS, false) + delta_grass_squares) == _neigh_size(g, i, j + 1, false)))
      return LOSING;
  }
  return REGULAR;  // regular move
}

/* ************************************************************************** */

bool game_is_over(cgame g) {
  assert(g);

  // check rule 1)
  for (uint i = 0; i < g->nb_rows; i++)
    for (uint j = 0; j < g->nb_cols; j++)
      if ((SQUARE(g, i, j) == TENT) && _neigh(g, i, j, TENT, !g->diagadj)) return false;

  // check rule 2)
  for (uint i = 0; i < g->nb_rows; i++)
    if (_nb_squares_row(g, i, TENT) != g->nb_tents_row[i]) return false;

  for (uint j = 0; j < g->nb_cols; j++)
    if (_nb_squares_col(g, j, TENT) != g->nb_tents_col[j]) return false;

  // check rule 3)
  if (_nb_squares(g, TREE) != _nb_squares(g, TENT)) return false;

  // check rule 4)
  for (uint i = 0; i < g->nb_rows; i++)
    for (uint j = 0; j < g->nb_cols; j++) {
      if ((SQUARE(g, i, j) == TENT) && !_neigh(g, i, j, TREE, false)) return false;
      if ((SQUARE(g, i, j) == TREE) && !_neigh(g, i, j, TENT, false)) return false;
    }

  return true;
}

/* ************************************************************************** */

void game_fill_grass_row(game g, uint i) {
  assert(g);
  assert(i < g->nb_rows);

  // fill row i
  for (uint j = 0; j < g->nb_cols; j++) {
    if (SQUARE(g, i, j) == EMPTY) game_play_move(g, i, j, GRASS);
  }
}

/* ************************************************************************** */

void game_fill_grass_col(game g, uint j) {
  assert(g);
  assert(j < g->nb_cols);

  // fill column j
  for (uint i = 0; i < g->nb_rows; i++) {
    if (SQUARE(g, i, j) == EMPTY) game_play_move(g, i, j, GRASS);
  }
}

/* ************************************************************************** */

void game_restart(game g) {
  for (uint i = 0; i < g->nb_rows; i++)
    for (uint j = 0; j < g->nb_cols; j++)
      if (SQUARE(g, i, j) != TREE) SQUARE(g, i, j) = EMPTY;

  // reset history
  _stack_clear(g->undo_stack);
  _stack_clear(g->redo_stack);
}

/* ************************************************************************** */
