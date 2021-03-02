#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

#include <stdbool.h>

#include "game.h"
#include "queue.h"

/**
 * @brief Game structure.
 * @details https://en.wikipedia.org/wiki/Opaque_data_type
 * @details https://en.wikipedia.org/wiki/Opaque_pointer
 */
struct game_s {
  uint nb_rows;       /**< number of rows in the game */
  uint nb_cols;       /**< number of columns in the game */
  uint *nb_tents_row; /**< the expected number of tents in each row */
  uint *nb_tents_col; /**< the expected number of tents in each col */
  square *squares;    /**< the grid of squares */
  bool wrapping;      /**< the wrapping option */
  bool diagadj;       /**< the diagadj option */
  queue *undo_stack;  /**< stack to undo moves */
  queue *redo_stack;  /**< stack to redo moves */
};

struct move_s {
  uint i, j;
  square old, new;
};

typedef struct move_s move;

#define INDEX(g, i, j) ((i) * (g->nb_cols) + (j))
#define SQUARE(g, i, j) ((g)->squares[(INDEX(g, i, j))])

#endif  // __GAME_STRUCT_H__
