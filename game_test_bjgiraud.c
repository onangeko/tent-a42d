#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_aux.h"


int test_game_get_expected_nb_tents_row(cgame g)
{
    assert ((game_get_expected_nb_tents_row(g,0)) == 3);
}

///

int test_game_get_expected_nb_tents_all(cgame g)
{
    assert(game_get_expected_nb_tents_all(g) == 12);
}

///

int test_game_get_expected_nb_tents_col(cgame g)
{
    assert(game_get_expected_nb_tents_col(g,0) == 4);
}

///////

int test_game_set_expected_nb_tents_row(cgame g)
{
    game_set_expected_nb_tents_row(g, 0, 3);

    assert (game_get_expected_nb_tents_row(g,0) == 3);


}

///////

int main(int argc, char* argv[]){

    cgame g1 = game_default();

    test_game_get_expected_nb_tents_row(g1);
    test_game_get_expected_nb_tents_all(g1);
    test_game_get_expected_nb_tents_col(g1);
    test_game_set_expected_nb_tents_row(g1);

}