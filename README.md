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
