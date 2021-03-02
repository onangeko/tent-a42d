/**
 * @file game_private.c
 * @copyright University of Bordeaux. All rights reserved, 2020.
 *
 **/

#include "game_private.h"
#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************** */
/*                                 GAME PRIV                                  */
/* ************************************************************************** */

char _square2str(square s) {
  if (s == EMPTY)
    return ' ';
  else if (s == TREE)
    return 'x';
  else if (s == TENT)
    return '*';
  else if (s == GRASS)
    return '-';
  else
    return '?';
}

/* ************************************************************************** */

int _str2square(char c) {
  if (c == ' ')
    return EMPTY;
  else if (c == 'x')
    return TREE;
  else if (c == '*')
    return TENT;
  else if (c == '-')
    return GRASS;
  else
    return -1;  // invalid
}

/* ************************************************************************** */

bool _inside(cgame g, int i, int j) {
  assert(g);
  if (game_is_wrapping(g)) {
    i = (i + game_nb_rows(g)) % game_nb_rows(g);
    j = (j + game_nb_cols(g)) % game_nb_cols(g);
  }
  if (i < 0 || j < 0 || i >= (int)g->nb_rows || j >= (int)g->nb_cols) return false;
  return true;
}

/* ************************************************************************** */

bool _inside_neigh(cgame g, int i, int j, direction dir) {
  if (dir == HERE) return _inside(g, i, j);
  if (dir == UP) return _inside(g, i - 1, j);
  if (dir == DOWN) return _inside(g, i + 1, j);
  if (dir == LEFT) return _inside(g, i, j - 1);
  if (dir == RIGHT) return _inside(g, i, j + 1);
  if (dir == UP_LEFT) return _inside(g, i - 1, j - 1);
  if (dir == UP_RIGHT) return _inside(g, i - 1, j + 1);
  if (dir == DOWN_LEFT) return _inside(g, i + 1, j - 1);
  if (dir == DOWN_RIGHT) return _inside(g, i + 1, j + 1);
  return false;
}

/* ************************************************************************** */

bool _test(cgame g, int i, int j, square s) {
  assert(g);
  assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);
  if (game_is_wrapping(g)) {
    i = (i + game_nb_rows(g)) % game_nb_rows(g);
    j = (j + game_nb_cols(g)) % game_nb_cols(g);
  }
  if (!_inside(g, i, j)) return false;
  return (SQUARE(g, i, j) == s);
}

/* ************************************************************************** */

bool _test_neigh(cgame g, int i, int j, square s, direction dir) {
  if (dir == HERE) return _test(g, i, j, s);
  if (dir == UP) return _test(g, i - 1, j, s);
  if (dir == DOWN) return _test(g, i + 1, j, s);
  if (dir == LEFT) return _test(g, i, j - 1, s);
  if (dir == RIGHT) return _test(g, i, j + 1, s);
  if (dir == UP_LEFT) return _test(g, i - 1, j - 1, s);
  if (dir == UP_RIGHT) return _test(g, i - 1, j + 1, s);
  if (dir == DOWN_LEFT) return _test(g, i + 1, j - 1, s);
  if (dir == DOWN_RIGHT) return _test(g, i + 1, j + 1, s);
  return false;
}

/* ************************************************************************** */

bool _neigh(cgame g, uint i, uint j, square s, bool diag) {
  assert(g);
  // assert(i < g->nb_rows && j < g->nb_cols);
  assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);

  // orthogonally
  if (_test_neigh(g, i, j, s, UP)) return true;
  if (_test_neigh(g, i, j, s, DOWN)) return true;
  if (_test_neigh(g, i, j, s, LEFT)) return true;
  if (_test_neigh(g, i, j, s, RIGHT)) return true;

  // diagonally
  if (diag) {
    if (_test_neigh(g, i, j, s, UP_LEFT)) return true;
    if (_test_neigh(g, i, j, s, UP_RIGHT)) return true;
    if (_test_neigh(g, i, j, s, DOWN_LEFT)) return true;
    if (_test_neigh(g, i, j, s, DOWN_RIGHT)) return true;
  }

  return false;
}

/* ************************************************************************** */

uint _neigh_size(cgame g, uint i, uint j, bool diag) {
  assert(g);
  // assert(i < g->nb_rows && j < g->nb_cols);

  uint size = 0;

  // orthogonally
  if (_inside_neigh(g, i, j, UP)) size++;
  if (_inside_neigh(g, i, j, DOWN)) size++;
  if (_inside_neigh(g, i, j, LEFT)) size++;
  if (_inside_neigh(g, i, j, RIGHT)) size++;

  // diagonally
  if (diag) {
    if (_inside_neigh(g, i, j, UP_LEFT)) size++;
    if (_inside_neigh(g, i, j, UP_RIGHT)) size++;
    if (_inside_neigh(g, i, j, DOWN_LEFT)) size++;
    if (_inside_neigh(g, i, j, DOWN_RIGHT)) size++;
  }

  return size;
}

/* ************************************************************************** */

uint _neigh_count(cgame g, uint i, uint j, square s, bool diag) {
  assert(g);
  // assert(i < g->nb_rows && j < g->nb_cols);

  uint count = 0;

  // orthogonally
  if (_test_neigh(g, i, j, s, UP)) count++;
  if (_test_neigh(g, i, j, s, DOWN)) count++;
  if (_test_neigh(g, i, j, s, LEFT)) count++;
  if (_test_neigh(g, i, j, s, RIGHT)) count++;

  // diagonally
  if (diag) {
    if (_test_neigh(g, i, j, s, UP_LEFT)) count++;
    if (_test_neigh(g, i, j, s, UP_RIGHT)) count++;
    if (_test_neigh(g, i, j, s, DOWN_LEFT)) count++;
    if (_test_neigh(g, i, j, s, DOWN_RIGHT)) count++;
  }

  return count;
}

/* ************************************************************************** */

uint _nb_squares_row(cgame g, uint i, square s) {
  assert(g);
  assert(i < g->nb_rows);
  uint nb_squares = 0;
  for (uint j = 0; j < g->nb_cols; j++)
    if (SQUARE(g, i, j) == s) nb_squares++;
  return nb_squares;
}

/* ************************************************************************** */

uint _nb_squares_col(cgame g, uint j, square s) {
  assert(g);
  assert(j < g->nb_cols);
  uint nb_squares = 0;
  for (uint i = 0; i < g->nb_rows; i++)
    if (SQUARE(g, i, j) == s) nb_squares++;
  return nb_squares;
}

/* ************************************************************************** */

uint _nb_squares(cgame g, square s) {
  assert(g);
  assert(s == EMPTY || s == TREE || s == TENT || s == GRASS);
  uint nb_squares = 0;
  for (uint i = 0; i < g->nb_rows; i++)
    for (uint j = 0; j < g->nb_cols; j++)
      if (SQUARE(g, i, j) == s) nb_squares++;
  return nb_squares;
}

/* ************************************************************************** */
/*                             STACK ROUTINES                                 */
/* ************************************************************************** */

void _stack_push_move(queue *q, move m) {
  assert(q);
  move *pm = malloc(sizeof(move));
  assert(pm);
  *pm = m;
  queue_push_head(q, pm);
}

/* ************************************************************************** */

move _stack_pop_move(queue *q) {
  assert(q);
  move *pm = queue_pop_head(q);
  assert(pm);
  move m = *pm;
  free(pm);
  return m;
}

/* ************************************************************************** */

bool _stack_is_empty(queue *q) {
  assert(q);
  return queue_is_empty(q);
}

/* ************************************************************************** */

void _stack_clear(queue *q) {
  assert(q);
  queue_clear_full(q, free);
  assert(queue_is_empty(q));
}

/* ************************************************************************** */
