#include <stdlib.h>
#include <stdio.h>

int dummy(char* str1)
{
    if (str1 == "dummy")
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int main(int argc, char* argv[]){
    
    dummy(argv[1]);

}