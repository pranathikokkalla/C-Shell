#include "main.h"

void fg1(int cmd_bytes, pid_t termpid,char command[][50])
{
    int i;
    for (i = 0; i < cmd_bytes; i++)
    {
        if (strcmp(command[i], ""))
        {
            cmdpointers1[i] = &command[i][0];
        }
        else
            cmdpointers1[i] = NULL;
    }
    int stat;
    pid_t pid = fork();
    if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(cmdpointers1[0], cmdpointers1) < 0)
        {
            fprintf(stderr, "Error executing %s command\n", cmdpointers1[0]);
            exit(1);
        }
    }
    else if (pid < 0)
    {
        perror("Forking Unsuccessful");
    }
    else if (pid > 0)
    {
        char processname1[500];
        char processname[500];

        strcpy(processname, cmdpointers1[0]);
        for (int i = 1; i < cmd_bytes; i++)
        {
            strcat(processname, " ");
            strcpy(processname1, processname);
            sprintf(processname, "%s%s", processname1, cmdpointers1[i]);
        }

        tcsetpgrp(0, pid);
        waitpid(pid, &stat, WUNTRACED);
        tcsetpgrp(0, termpid);

        if (WIFSTOPPED(stat))
        {
            array[processcount].pid = pid;
            array[processcount].status = 1;
            strcpy(array[processcount++].name, processname);
        }
    }
}