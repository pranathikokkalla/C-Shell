#include "main.h"

void echo(int cmd_bytes, char command[][50])
{
    int i;
    for (i = 1; i < cmd_bytes; i++)
    {
        printf("%s ", command[i]);
    }
    printf("\n");
}

void pwd()
{
    char cwd[200];
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("Can not get the current working directory\n");
    }
}