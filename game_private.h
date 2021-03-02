/**
 * @file game_private.h
 * @brief Private Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2020.
 **/

#ifndef __GAME_PRIVATE_H__
#define __GAME_PRIVATE_H__

#include <stdbool.h>

#include "game.h"
#include "queue.h"

/* ************************************************************************** */
/*                             DATA TYPES                                     */
/* ************************************************************************** */

/**
 * @brief Game structure.
 * @details This is an opaque data type.
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

/**
 * @brief Move structure.
 * @details This structure is used to save the game history.
 */
struct move_s {
  uint i, j;
  square old, new;
};

typedef struct move_s move;

typedef enum { HERE, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT } direction;

/* ************************************************************************** */
/*                                MACRO                                       */
/* ************************************************************************** */

#define INDEX(g, i, j) ((i) * (g->nb_cols) + (j))
#define SQUARE(g, i, j) ((g)->squares[(INDEX(g, i, j))])

/* ************************************************************************** */
/*                             STACK ROUTINES                                 */
/* ************************************************************************** */

/** push a move in the stack */
void _stack_push_move(queue *q, move m);

/** pop a move from the stack */
move _stack_pop_move(queue *q);

/** test if the stack is empty */
bool _stack_is_empty(queue *q);

/** clear all the stack */
void _stack_clear(queue *q);

/* ************************************************************************** */
/*                          GAME PRIVATE ROUTINES                             */
/* ************************************************************************** */

/**
 * @brief convert a square into a character
 *
 * @param s a square
 * @return the corresponding character, '?' otherwise
 */
char _square2str(square s);

/**
 * @brief convert a character into square
 *
 * @param c character
 * @return the corresponding square value, -1 otherwise
 */
int _str2square(char c);

/**
 * @brief test if a given square is inside the board
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @return true if inside, false otherwise
 */
bool _inside(cgame g, int i, int j);

/**
 * @brief test if the neighbour of a given square is inside the board
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @param dir the direction in which to consider the neighbour
 * @return true if inside, false otherwise
 */
bool _inside_neigh(cgame g, int i, int j, direction dir);

/**
 * @brief test if a square has a given value
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value to be compared
 * @return true if equal, false otherwise
 */
bool _test(cgame g, int i, int j, square s);

/**
 * @brief test if the neighbour square has a given value
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value to be compared
 * @param dir the direction in which to consider the neighbour
 * @return true if equal, false otherwise
 */
bool _test_neigh(cgame g, int i, int j, square s, direction dir);

/**
 * @brief test if a square can be found in the neighbourhood of another
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value to look for
 * @param diag enable diagonal adjacency
 * @return true if found, false otherwise
 */
bool _neigh(cgame g, uint i, uint j, square s, bool diag);

/**
 * @brief get the neighbourhood size
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @param diag enable diagonal adjacency
 *
 * @return the neighbourhood size
 */
uint _neigh_size(cgame g, uint i, uint j, bool diag);

/**
 * @brief get the number of squares with a certain value in the neighbourhood of
 * a given square
 *
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value to look for
 * @param diag enable diagonal adjacency
 * @return the number of squares found
 */
uint _neigh_count(cgame g, uint i, uint j, square s, bool diag);

/**
 * @brief get the number of squares with a certain value in a row
 *
 * @param g the game
 * @param i row index
 * @param s the square value to look for
 * @return the number of squares found
 */
uint _nb_squares_row(cgame g, uint i, square s);

/**
 * @brief get the number of squares with a certain value in a column
 *
 * @param g the game
 * @param j column index
 * @param s the square value to look for
 * @return the number of squares found
 */
uint _nb_squares_col(cgame g, uint j, square s);

/**
 * @brief get the number of squares with a certain value in the board
 *
 * @param g the game
 * @param s the square value to look for
 * @return the number of squares found
 */
uint _nb_squares(cgame g, square s);

#endif  // __GAME_PRIVATE_H__
