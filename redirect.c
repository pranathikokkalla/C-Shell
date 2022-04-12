#include "main.h"

int redirect(int cmd_bytes, char command[][50])
{
    int i, input, output;
    int c1 = 0, c2 = 0, c3 = 0;

    for (i = 0; i <= cmd_bytes - 2; i++)
    {
        if (strcmp(command[i], "<") == 0)
            c1 = 1;
        if (strcmp(command[i], ">") == 0)
            c2 = 1;
        if (strcmp(command[i], ">>") == 0)
            c3 = 1;
    }
    if (c1)
    {
        for (i = 0; i <= cmd_bytes - 2; i++)
        {
            if (strcmp(command[i], "<") == 0)
            {
                input = open(&command[i + 1][0], O_RDONLY);
                if (input < 0)
                {
                    printf("Error opening the file %s\n", command[i + 1]);
                    return 0;
                }
                else
                {
                    dup2(input, STDIN_FILENO);
                    close(input);
                }
                strcpy(command[i], "");
                strcpy(command[i + 1], "");
                break;
            }
        }
    }
    if (c2)
    {
        for (i = 0; i <= cmd_bytes - 2; i++)
        {
            if (strcmp(command[i], ">") == 0)
            {
                output = open(&command[i + 1][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output < 0)
                {
                    printf("Error opening the file %s\n", command[i + 1]);
                    return 0;
                }
                else
                {
                    dup2(output, STDOUT_FILENO);
                    close(output);
                }
                strcpy(command[i], "");
                strcpy(command[i + 1], "");
                break;
            }
        }
    }
    if (c3)
    {
        for (i = 0; i <= cmd_bytes - 2; i++)
        {
            if (strcmp(command[i], ">>") == 0)
            {
                output = open(&command[i + 1][0], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (output < 0)
                {
                    printf("Error opening the file %s\n", command[i + 1]);
                    return 0;
                }
                else
                {
                    dup2(output, STDOUT_FILENO);
                    close(output);
                }
                strcpy(command[i], "");
                strcpy(command[i + 1], "");
                break;
            }
        }
    }
    for (i = 0; i <= cmd_bytes - 2; i++)
    {
        if (strcmp(command[i], ">>") == 0 || strcmp(command[i], ">") == 0 || strcmp(command[i], "<") == 0)
        {
            printf("Incorrect command\n");
            return 0;
        }
    }
    return 1;
}
