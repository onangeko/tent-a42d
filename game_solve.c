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
        exit(EXIT_FAILURE);
    }
    input_file = argv[optind];
    FILE* fptr;
    //Checks if output file is specified
    if (argv[optind + 1] != NULL) {
        output = true;
        fptr = fopen(argv[optind + 1], "w");
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
                char* solution = malloc((game_nb_rows(g) + 4) * (game_nb_cols(g) * 6) * sizeof(char));
                freopen("/dev/null", "a", stdout);
                setbuf(stdout, solution);
                game_print(g);
                if (solution == NULL)
                    solution = "";
                fprintf(fptr, "%s", solution);
                fclose(fptr);
                free(solution);
            }
            //Else just print the game
            else {
                game_print(g);
            }
        }
    }
    game_delete(g);
}
