#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void)
{
    void *retaddr;
    char buf [76];

    fflush(stdout);
    gets(buf);
    if (((uint)retaddr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n",retaddr);
        exit(1);
    }
    puts(buf);
    strdup(buf);
}

void main(void)
{
    p();
}