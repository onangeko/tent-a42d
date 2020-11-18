#include "game.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct game_s {
  square** board;
  int* expected_nb_tents_col;
  int* expected_nb_tents_row;
} game_s;

game game_new(square* squares, uint* nb_tents_row, uint* nb_tents_col) {
  if(squares==NULL || nb_tents_row == NULL || nb_tents_col == NULL){
        exit(EXIT_FAILURE);
    }
    struct game_s *game =(struct game_s*) malloc(sizeof(struct game_s));
    game->board = (square **) malloc(sizeof(square)*DEFAULT_SIZE*DEFAULT_SIZE);
    game->expected_nb_tents_row = nb_tents_row;
    game->expected_nb_tents_row = nb_tents_col;
    for(int i=0;i<DEFAULT_SIZE;i++)
    {
        for(int j=0;j<DEFAULT_SIZE;j++)
        {
            game->board[i][j]=squares[i*DEFAULT_SIZE+j];
        }
    }
    return game;
}

game game_new_empty(void) { return NULL; }

game game_copy(cgame g) { return NULL; }

bool game_equal(cgame g1, cgame g2) { return NULL; }

void game_delete(game g) {}

void game_set_square(game g, uint i, uint j, square s) {}

square game_get_square(cgame g, uint i, uint j) { return EMPTY; }

void game_set_expected_nb_tents_row(game g, uint i, uint nb_tents) {}

void game_set_expected_nb_tents_col(game g, uint j, uint nb_tents) {}

uint game_get_expected_nb_tents_row(cgame g, uint i) { return 0; }

uint game_get_expected_nb_tents_col(cgame g, uint j) { return 0; }

uint game_get_expected_nb_tents_all(cgame g) { return 0; }

uint game_get_current_nb_tents_row(cgame g, uint i) { return 0; }

uint game_get_current_nb_tents_col(cgame g, uint j) { return 0; }

uint game_get_current_nb_tents_all(cgame g) { return 0; }

void game_play_move(game g, uint i, uint j, square s) {}

int game_check_move(cgame g, uint i, uint j, square s) { return ILLEGAL; }

bool game_is_over(cgame g) { return false; }

void game_fill_grass_row(game g, uint i) {}

void game_fill_grass_col(game g, uint j) {}

<<<<<<< HEAD
void game_restart(game g) {}
=======
>>>>>>> 863cb1a1b2915fe5d05a151cce0ef5bc02cfca2b
