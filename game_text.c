#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints the help guide in the terminal.
 */
void printHelp()
{
    printf("- press \'t <i> <j>\' to put a tent at square (i,j)\n");
    printf("- press \'g <i> <j>\' to put grass at square (i,j)\n");
    printf("- press \'e <i> <j>\' to erase square (i,j)\n");
    printf("- press \'r\' to restart\n");
    printf("- press \'q\' to quit\n");
    printf("- press \'s\' to save the current game\n");
}

/**
 * Prints the shame message in the terminal.
 */
void printShame()
{
    printf("Shame!\n\n");
}

/**
 * Prints the win message in the terminal.
 */
void printCongratulation()
{
    printf("Congratulation!\n");
}

/**
 * Prints the illegal message in the terminal.
 */
void printIllegal()
{
    printf("Wait... It's illegal.\n");
}

/**
 * Prints the losing message in the terminal.
 */
void printLosing()
{
    printf("Warning: losing move...\n");
}

/**
 * Restarts the game.
 * @param g the game.
 */
void restartGame(game g)
{
    printf("> Restart the game.\n");
    game_restart(g);
}

/**
 * Returns a default solution according to the original default game on the website but without grass blocs.
 * @return the default game solution without grass
 */
game game_default_solution_without_grass(void)
{
    game defaultSolution = game_default();
    //Plant tents and grass by rows
    //row 0
    //Tents
    game_set_square(defaultSolution, 0, 0, TENT);
    game_set_square(defaultSolution, 0, 3, TENT);
    game_set_square(defaultSolution, 0, 6, TENT);
    //row 1
    //No tent
    //row 2
    //Tents
    game_set_square(defaultSolution, 2, 0, TENT);
    game_set_square(defaultSolution, 2, 3, TENT);
    game_set_square(defaultSolution, 2, 5, TENT);
    game_set_square(defaultSolution, 2, 7, TENT);
    //row 3
    //No tent
    //row 4
    //Tents
    for (int i = 0; i < 7; i += 2) {
        game_set_square(defaultSolution, 4, i, TENT);
    }
    //row 5
    //No tent
    //row 6
    //Tent
    game_set_square(defaultSolution, 6, 0, TENT);
    //row 7
    //No tent
    //Grass
    return defaultSolution;
}

/**
 * Process the client command.
 * @param g the game.
 * @param inst the instruction.
 * @param row the row index.
 * @param column the column index.
 * @return true if the process ends properly, false otherwise.
 */
int answerProcessing(game g, char inst, int row, int column)
{
    char * current = "current.tnt";
    // 1st treatment of scanf()
    if (row == -1 && column == -1) {
        switch (inst) {
        case 'r':
            restartGame(g);
            return 1;
        case 'h':
            printHelp();
            return 1;
        case 'q':
            printShame();
            game_delete(g);
            exit(EXIT_SUCCESS);
        case 'z':
            game_undo(g);
            return 1;
        case 'y':
            game_redo(g);
            return 1;
        case 's': ;
        
            game_save(g,current);
        default:
            break;
        }
        return 0;
    }
    //2nd treatment of scanf()
    else {
        switch (inst) {
        // Tent planting
        case 't':
            if (game_check_move(g, row, column, TENT) == REGULAR) {
                printf("> Plant a tent on %d %d\n", row, column);
                game_play_move(g, row, column, TENT);
                if (game_is_over(g)) {
                    printCongratulation();
                }
                return 1;
            } else if (game_check_move(g, row, column, TENT) == LOSING) {
                game_play_move(g, row, column, TENT);
                printLosing();
                return 1;
            } else //illegal move
            {
                printIllegal();
                return 1;
            }
            break;
        // Grass puting
        case 'g':
            if (game_check_move(g, row, column, GRASS) == REGULAR) {
                printf("> Plant a grass bloc on %d %d\n", row, column);
                game_play_move(g, row, column, GRASS);
                if (game_is_over(g)) {
                    printCongratulation();
                }
                return 1;
            } else if (game_check_move(g, row, column, GRASS) == LOSING) {
                game_play_move(g, row, column, GRASS);
                printLosing();
                return 1;
            } else //illegal move
            {
                printIllegal();
                return 1;
            }
            break;
        // Square erasing
        case 'e':
            if (game_check_move(g, row, column, EMPTY) == REGULAR) {
                printf("> Set %d %d bloc to empty\n", row, column);
                game_play_move(g, row, column, EMPTY);
                return 1;
            } else if (game_check_move(g, row, column, EMPTY) == ILLEGAL) {
                printIllegal();
                return 1;
            }
            break;
        default:
            printf("\"%c\" Commande inconnue\n", inst);
            return 0;
            break;
        }
    }
    return -1;
}

int main(int argc, char* argv[])
{
    game g ;
    if (argv[1] == NULL)
    {
        g = game_default();
    }
    else
    {
        g = game_load(argv[1]);
    }
    while (!game_is_over(g)) {
        //Default values
        char instruction = '\n';
        int row = -1;
        int column = -1;
        game_print(g);
        printf("> ? [h for help]\n");
        //While the client press enter without a command
        while (instruction == '\n') {
            scanf(" %c", &instruction);
            // Answer will be 0 if the command is not a single term expression ('h','r','q')
            int answer = answerProcessing(g, instruction, row, column);
            // Process the other arguments
            if (!answer && scanf(" %d %d", &row, &column) == 2) {
                answerProcessing(g, instruction, row, column);
            }
        }
    }
    game_print(g);
    // free the game
    game_delete(g);
    return EXIT_SUCCESS;
}  


