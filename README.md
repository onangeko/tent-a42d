## Tests
### game.h

Bjorn:
* game_set_expected_nb_tents_row
* game_set_expected_nb_tents_col
* game_get_expected_nb_tents_row
* game_get_expected_nb_tents_col
* game_get_expected_nb_tents_all

Emile:
* game_equal
* game_copy
* game_new
* game_new_empty
* game_delete

Mathis:
* game_get_square
* game_set_square
* game_play_move
* game_check_move
* game_fill_grass_row
* game_fill_grass_col

Olivier:
* game_restart
* game_is_over
* game_get_current_nb_tents_all
* game_get_current_nb_tents_col
* game_get_current_nb_tents_row

### game_aux.h

Olivier:
* game_print

Bjorn:
* game_default_solution

Emile:
* game_default

## game.c implementation

Bjorn:
* game_set_expected_nb_tents_row
* game_set_expected_nb_tents_col
* game_get_expected_nb_tents_row
* game_get_expected_nb_tents_col
* game_get_expected_nb_tents_all

Emile:
* game_equal
* game_copy
* game_new
* game_new_empty
* game_delete

Mathis:
* game_get_square
* game_set_square
* game_play_move
* game_check_move
* game_fill_grass_row
* game_fill_grass_col

Olivier:
* game_restart
* game_is_over
* game_get_current_nb_tents_all
* game_get_current_nb_tents_col
* game_get_current_nb_tents_row

## game_ext.h implementation

Bjorn:
* game_nb_rows
* game_nb_cols

Emile:
* game_new_ext
* game_new_empty_ext
* game_undo
* game_redo

Mathis:
* game_undo
* game_redo

Olivier:
* game_is_wrapping
* game_is_diagadj

## Saving system
# Format

    <nb_rows> <nb_cols> <is_swap> <is_diagadj>\n
    <nb_tents_row[0]> <nb_tents_row[1]> ... <nb_tents_row[nb_rows-1]> \n
    <nb_tents_col[0]> <nb_tents_col[1]> ... <nb_tents_col[nb_cols-1]> \n
    <squares[0][0]><squares[0][1]>...<squares[0][nb_cols-1]>\n
    <squares[1][0]><squares[1][1]>...<squares[1][nb_cols-1]>\n

    The first line describes in that order the number of grid rows <nb_rows>, the number of grid columns <nb_cols>, is the topology wrapping or not <is_wrapping> (0 for false and 1 for true) and do diagonals count for ajdacency <is_diagadj> (0 for false and 1 for true). Then, the second line indicates for each line, the number of expected tents (the values are separated by spaces and there is a space at the end of the line). The third line, indicates for each column the number of expected tents (the values are separated by spaces and there is a space at the end of the line). Finally the following lines store the content of each square of the grid with one character (' ' for EMPTY, 'x' for TREE, '*' for TENT, '-' for GRASS). In particular, <squares[i][j]> describes the content of the square in the i-th row and j-th column.

##Solver

Bjorn:
* game_solve.c
Emile:
* game_solve
Mathis:
* game_nb_solutions
Olivier:
* game_solve.c

##SDL
* render()


* adapter l'affichage au dimension courante de la fenetre
* implémenter les fonctions de game_text (undo, redo, tent, grass, empty, ...)
* implémenter un affichage pour les illegal et losing move
* Raccourcis claviers pour le jeu en graphique:
* z : Undo
* y : Redo
* r : Restart
* s : Save
* t : Solve
* q/ESC : Quit

Bjorn:
* clean()
* process()

Emile:

Mathis:
* init()

Olivier:
