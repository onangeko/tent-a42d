/**
 * @file game.h
 * @brief Basic Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2020.
 **/

#ifndef __GAME_H__
#define __GAME_H__
#include <stdbool.h>

/**
 * @brief Standard unsigned integer type.
 **/
typedef unsigned int uint;

/**
 * @brief Size of the default game grid.
 **/
#define DEFAULT_SIZE 8

/**
 * @brief Different kinds of square used in the game.
 **/
typedef enum {
  EMPTY = 0, /**< empty square */
  TREE = 1,  /**< tree square */
  TENT = 2,  /**< tent square */
  GRASS = 3, /**< grass square */
} square;

/**
 * @brief Different kinds of move used in the game.
 **/
enum {
  ILLEGAL = 0, /**< illegal move */
  REGULAR = 1, /**< regular move */
  LOSING = 2,  /**< losing move */
};

/**
 * @brief The structure pointer that stores the game state.
 **/
typedef struct game_s *game;

/**
 * @brief The structure constant pointer that stores the game state.
 * @details That means that it is not possible to modify the game using this
 * pointer.
 **/
typedef const struct game_s *cgame;

/**
 * @brief Creates a new game with default size and initializes it.
 * @param squares an array describing the initial square values (row-major
 * storage)
 * @param nb_tents_row an array with the expected number of tents in each row
 * @param nb_tents_col an array with the expected number of tents in each column
 * @pre @p squares must be an initialized array of default size squared.
 * @pre @p nb_tents_row must be an initialized array of default size.
 * @pre @p nb_tents_col must be an initialized array of default size.
 * @return the created game
 **/
game game_new(square *squares, uint *nb_tents_row, uint *nb_tents_col);

/**
 * @brief Creates a new empty game with defaut size.
 * @details All squares are initialized with empty squares, and the expected
 * numbers of tents for each row/column are set to zero.
 * @return the created game
 **/
game game_new_empty(void);

/**
 * @brief Duplicates a game.
 * @param g the game to copy
 * @return the copy of the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
game game_copy(cgame g);

/**
 * @brief Tests if two games are equal.
 * @param g1 the first game
 * @param g2 the second game
 * @return true if the two games are equal, false otherwise
 * @pre @p g1 must be a valid pointer toward a game structure.
 * @pre @p g2 must be a valid pointer toward a game structure.
 **/
bool game_equal(cgame g1, cgame g2);

/**
 * @brief Deletes the game and frees the allocated memory.
 * @param g the game to delete
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_delete(game g);

/**
 * @brief Sets the value of a given square.
 * @details This function is useful for initializing the squares of an empty
 * game.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 * @pre @p j < game height
 * @pre @p s must be either EMPTY, GRASS, TENT or TREE.
 **/
void game_set_square(game g, uint i, uint j, square s);

/**
 * @brief Gets the value of a given square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 * @pre @p j < game height
 * @return the square value
 **/
square game_get_square(cgame g, uint i, uint j);

/**
 * @brief Sets the expected number of tents in a given row.
 * @param g the game
 * @param i row index
 * @param nb_tents the expected number of tents on this row
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 **/
void game_set_expected_nb_tents_row(game g, uint i, uint nb_tents);

/**
 * @brief Sets the expected number of tents in a given column.
 * @param g the game
 * @param j column index
 * @param nb_tents the expected number of tents on this column
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p j < game height
 **/
void game_set_expected_nb_tents_col(game g, uint j, uint nb_tents);

/**
 * @brief Gets the expected number of tents in a given row.
 * @param g the game
 * @param i row index
 * @return the expected number of tents on this row
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 **/
uint game_get_expected_nb_tents_row(cgame g, uint i);

/**
 * @brief Gets the expected number of tents in a given column.
 * @param g the game
 * @param j column index
 * @return the expected number of tents on this column
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p j < game height
 **/
uint game_get_expected_nb_tents_col(cgame g, uint j);

/**
 * @brief Gets the expected number of tents on the whole grid.
 * @param g the game
 * @return the expected number of tents on this game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
uint game_get_expected_nb_tents_all(cgame g);

/**
 * @brief Gets the current number of tents in a given row.
 * @param g the game
 * @param i row index
 * @return the current number of tents on this row
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 **/
uint game_get_current_nb_tents_row(cgame g, uint i);

/**
 * @brief Gets the current number of tents in a given column.
 * @param g the game
 * @param j column index
 * @return the expected number of tents on this column
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p j < game height
 **/
uint game_get_current_nb_tents_col(cgame g, uint j);

/**
 * @brief Gets the current number of tents on the whole grid.
 * @param g the game
 * @return the current number of tents on this game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
uint game_get_current_nb_tents_all(cgame g);

/**
 * @brief Plays a move in a given square.
 * @details This function allows to play both a regular or a losing move, but
 * not an illegal move (see @ref index).
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 * @pre @p j < game height
 * @pre @p s must be either EMPTY, GRASS or TENT (but not TREE).
 * @pre The game square at position (i,j) must not be TREE.
 **/
void game_play_move(game g, uint i, uint j, square s);

/**
 * @brief Checks if a given move in a square is regular
 * @details This function checks that playing a move in a square is a regular
 * move (see @ref index).
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @return either REGULAR, LOSING or ILLEGAL depending on the move
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 * @pre @p j < game height
 * @pre @p s must be either EMPTY, GRASS, TENT or TREE.
 **/
int game_check_move(cgame g, uint i, uint j, square s);

/**
 * @brief Checks if the game is won.
 * @param g the game
 * @details This function checks that all the game rules (decribed on @ref
 * index) are satisfied, and more specifically that all the tents are correctly
 * placed. The remaining squares are either empty square or grass square.
 * @return true if the game ended successfully, false otherwise
 * @pre @p g must be a valid pointer toward a game structure.
 **/
bool game_is_over(cgame g);

/**
 * @brief Fills a row with grass.
 * @details This function only puts grass on empty squares, without modifying
 * the other squares.
 * @param g the game
 * @param i row index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game width
 */
void game_fill_grass_row(game g, uint i);

/**
 * @brief Fills a column with grass.
 * @details This function only puts grass on empty squares, without modifying
 * the other squares.
 * @param g the game
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p j < game height
 */
void game_fill_grass_col(game g, uint j);

/**
 * @brief Restarts a game.
 * @details All the game is reset to its initial state. In particular, all the
 * squares except trees are reset to empty state.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_restart(game g);

#endif  // __GAME_H__