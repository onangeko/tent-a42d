#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char
test(char *arg)
{
    if (strcmp("dummy", arg) == 0)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
    

int
main(int argc, char *argv[])
{
    return test(argv[1]);
}
