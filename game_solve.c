#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    game g = game_load("saveTest.tnt");
    bool solved = game_solve(g);
    printf(solved ? "true" : "false");
    game_print(g);
}