/**
 * @file game_aux.h
 * @brief Auxiliarry Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2020.
 *
 **/

#ifndef __GAME_AUX_H__
#define __GAME_AUX_H__
#include <stdbool.h>
#include "game.h"

/**
 * @brief Prints a game as text on the standard output stream.
 * @details The different squares EMPTY, TREE, TENT, and GRASS are respectively
 * displayed with the following characters ' ', 'x', '*', '-'.
 * Here is the attempted output for the default game:
@verbatim
   01234567
   --------
0 |    xx  | 3
1 |x      x| 0
2 |    x   | 4
3 |x    x  | 0
4 | x      | 4
5 |x   x x | 0
6 |        | 1
7 |x       | 0
   --------
   40121121
@endverbatim
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_print(cgame g);

/**
 * @brief Creates the default game.
 * @details See the description of the default game in @ref index.
 * @details https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/tents.html#8x8de#911105660705777
 * @return the created game
 **/
game game_default(void);

/**
 * @brief Creates the default game solution.
 * @details See the description of the default game in @ref index.
 * @details https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/tents.html#8x8de#911105660705777
 * @return the created game
 **/
game game_default_solution(void);

#endif  // __GAME_AUX_H__