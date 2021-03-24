#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXCHAR = 1000

int main(int argc, char* argv[])
{
    bool solve = false;
    bool count = false;
    bool output = false;
    char* input_file;
    char* output_file;
    int c;
    while ((c = getopt(argc, argv, "sc")) != -1) {
        switch (c) {
        case 's':
            solve = true;
            break;
        case 'c':
            count = true;
            break;
        case '?':
            printf("unknown option:%c\n", optopt);
            break;
        }
    }
    if (argv[optind] == NULL) {
        fprintf(stderr, "Rentrez un jeu en argument | error game_solve");
        exit(EXIT_FAILURE);
    }
    input_file = argv[optind];
    FILE* fptr;
    //Checks if output file is specified
    if (argv[optind + 1] != NULL) {
        output = true;
        output_file = argv[optind + 1];
        fptr = fopen(output_file, "w");
    }
    //If -c is present
    game g = game_load(input_file);
    if (count) {
        int nb_sol = game_nb_solutions(g);
        if (output) {
            fprintf(fptr, "Number of solutions found -> %d\n", nb_sol);
        } else {
            printf("Number of solutions found -> %d\n", nb_sol);
        }
    }
    //If -s is present
    if (solve) {
        if (game_solve(g)) {
            //Saves the output of game_print into the output file
            if (output) {
                game_save(g, output_file);
            }
            //Else just print the game
            else {
                game_print(g);
            }
        } else {
            printf("No solution found for %s\n", input_file);
        }
    }
    game_delete(g);
}
