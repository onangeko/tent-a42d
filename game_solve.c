#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc >= 2) {
        game g = game_load(argv[1]);
        game_print(g);
        printf(game_solve(g) ? "solved\n" : "not solved\n");
        game_print(g);
    }
}