#include <stdlib.h>
#include <stdio.h>

void run(void)
{
    fwrite("Good... Wait what?\n", 1, 19, stdout);
    system("/bin/sh");
}

int main(void)
{
    char buf[76];

    gets(buf);
    return 0;
}
