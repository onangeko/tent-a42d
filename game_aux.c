/**
 * @file game_aux.c
 * @copyright University of Bordeaux. All rights reserved, 2020.
 *
 **/

#include "game_aux.h"
#include "game.h"
#include "game_ext.h"
#include "game_private.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************** */

void game_print(cgame g) {
  assert(g);
  printf("   ");
  for (uint j = 0; j < game_nb_cols(g); j++) printf("%d", j);
  printf("\n");
  printf("   ");
  for (uint j = 0; j < game_nb_cols(g); j++) printf("-");
  printf("\n");
  for (uint i = 0; i < game_nb_rows(g); i++) {
    printf("%d |", i);
    for (uint j = 0; j < game_nb_cols(g); j++) {
      square s = game_get_square(g, i, j);
      char c = _square2str(s);
      printf("%c", c);
    }
    printf("| %d\n", game_get_expected_nb_tents_row(g, i));
  }
  printf("   ");
  for (uint j = 0; j < game_nb_cols(g); j++) printf("-");
  printf("\n");
  printf("   ");
  for (uint j = 0; j < game_nb_cols(g); j++) printf("%d", game_get_expected_nb_tents_col(g, j));
  printf("\n");
}

/* ************************************************************************** */

game game_default(void) {
  square squares[] = {
      EMPTY, EMPTY, EMPTY, EMPTY, TREE,  TREE,  EMPTY, EMPTY, /* row 0 */
      TREE,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, TREE,  /* row 1 */
      EMPTY, EMPTY, EMPTY, EMPTY, TREE,  EMPTY, EMPTY, EMPTY, /* row 2 */
      TREE,  EMPTY, EMPTY, EMPTY, EMPTY, TREE,  EMPTY, EMPTY, /* row 3 */
      EMPTY, TREE,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, /* row 4 */
      TREE,  EMPTY, EMPTY, EMPTY, TREE,  EMPTY, TREE,  EMPTY, /* row 5 */
      EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, /* row 6 */
      TREE,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, /* row 7 */
  };
  uint nb_tents_row[] = {3, 0, 4, 0, 4, 0, 1, 0};
  uint nb_tents_col[] = {4, 0, 1, 2, 1, 1, 2, 1};
  return game_new(squares, nb_tents_row, nb_tents_col);
}

/* ************************************************************************** */

game game_default_solution(void) {
  game g = game_default();
  game_play_move(g, 0, 0, TENT);
  game_play_move(g, 0, 3, TENT);
  game_play_move(g, 0, 6, TENT);
  game_play_move(g, 2, 0, TENT);
  game_play_move(g, 2, 3, TENT);
  game_play_move(g, 2, 5, TENT);
  game_play_move(g, 2, 7, TENT);
  game_play_move(g, 4, 0, TENT);
  game_play_move(g, 4, 2, TENT);
  game_play_move(g, 4, 4, TENT);
  game_play_move(g, 4, 6, TENT);
  game_play_move(g, 6, 0, TENT);
  for (uint i = 0; i < DEFAULT_SIZE; i++) game_fill_grass_row(g, i);
  return g;
}

/* ************************************************************************** */
