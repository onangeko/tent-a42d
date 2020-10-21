#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_aux.h"

int dummy(char *arg)
{
    if (strcmp("dummy", arg) == 0)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    return dummy(argv[1]);
}