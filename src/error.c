#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "error.h"

void 
exit_perror(char *str)
{
    perror(str);
    exit(1);
}

void
exit_error(char *str)
{
    fprintf(stderr,"%s\n",str);
    exit(1);
}
