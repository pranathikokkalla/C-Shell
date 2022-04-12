#include "main.h"

void piping(int cmd_bytes, char *cmd, pid_t termpid, char *path, char command[][50])
{
    int i, j, no_of_pipes = 0, input, output;
    int pipes[50][2];

    if (strcmp(command[0], "|") == 0)
    {
        printf("Incorrect command\n");
        return;
    }
    if (strcmp(command[cmd_bytes - 1], "|") == 0)
    {
        printf("Incorrect command\n");
        return;
    }
    for (i = 0; i < cmd_bytes - 1; i++)
    {
        if (strcmp(command[i], "|") == 0)
        {
            no_of_pipes++;
        }
    }

    int count = 0;
    char pipelist[50][50];

    char *token = strtok(cmd, "|");
    while (token != NULL)
    {
        strcpy(pipelist[count], token);
        count++;
        token = strtok(NULL, "|");
    }

    if (count - 1 != no_of_pipes)
    {
        printf("Incorrect command\n");
        return;
    }

    int pipecmd_bytes;
    char pipecommand[50][50];

    output = dup(1);
    pipecmd_bytes = 0;
    token = strtok(pipelist[0], " \t");
    while (token != NULL)
    {
        strcpy(pipecommand[pipecmd_bytes], token);
        pipecmd_bytes++;
        token = strtok(NULL, " \t");
    }

    if (pipe(pipes[0]) < 0)
    {
        perror("Error:");
    }

    dup2(pipes[0][1], 1);
    execute(pipecmd_bytes, termpid, path, pipecommand);
    dup2(output, 1);
    close(pipes[0][1]);
    close(output);

    for (j = 0; j < pipecmd_bytes; j++)
    {
        strcpy(pipecommand[j], "");
    }

    for (i = 1; i < count; i++)
    {
        output = dup(1);
        input = dup(0);
        pipecmd_bytes = 0;

        token = strtok(pipelist[i], " \t");
        while (token != NULL)
        {
            strcpy(pipecommand[pipecmd_bytes], token);
            pipecmd_bytes++;
            token = strtok(NULL, " \t");
        }

        if (pipe(pipes[i]) < 0)
        {
            perror("Error:");
        }
        else if (i == count - 1)
        {
            dup2(pipes[count - 2][0], 0);
            execute(pipecmd_bytes, termpid, path, pipecommand);
            dup2(input, 0);
            close(pipes[count - 2][0]);
        }
        else
        {
            dup2(pipes[i][1], 1);
            dup2(pipes[i - 1][0], 0);
            execute(pipecmd_bytes, termpid, path, pipecommand);
            dup2(input, 0);
            dup2(output, 1);
            close(pipes[i][1]);
            close(pipes[i - 1][0]);
        }
        for (j = 0; j < pipecmd_bytes; j++)
        {
            strcpy(pipecommand[j], "");
        }
        close(input);
        close(output);
    }
    // printf("hi");
    dup2(shellin, 0);
    dup2(shellout, 1);
}