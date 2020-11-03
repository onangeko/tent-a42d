#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool dummy(char * argv)
{
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    return dummy(argv[1]);
}
