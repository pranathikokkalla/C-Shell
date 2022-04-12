#include "main.h"

void bg(int cmd_bytes, char command[][50], pid_t termpid)
{
    int j = 0;
    pid_t pid;
    int stat;
    char *cmdpointers[1024];
    for (int i = 0; i < cmd_bytes; i++)
    {
        cmdpointers[i] = &command[i][0];
    }
    for (int i = 0; i < cmd_bytes; i++)
    {
        if (strcmp(cmdpointers[i], "&"))
        {
            cmdpointers[j++] = cmdpointers[i];
        }
    }
    cmdpointers[j] = NULL;
    pid = fork();
    if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(cmdpointers[0], cmdpointers) < 0)
        {
            fprintf(stderr, "Error executing %s command\n", cmdpointers[0]);
            exit(1);
        }
    }
    else if (pid < 0)
    {
        perror("Forking Unsuccessful");
    }
    else if (pid > 0)
    {
        // dup2(shellout, STDOUT_FILENO);
        // dup2(shellin, STDIN_FILENO);

        char processname1[500];
        char processname[500];
        strcpy(processname, cmdpointers[0]);
        for (int i = 1; i < j; i++)
        {
            strcat(processname, " ");
            strcpy(processname1, processname);
            sprintf(processname, "%s%s", processname1, cmdpointers[i]);
        }
        array[processcount].pid = pid;
        array[processcount].status = 1;
        strcpy(array[processcount++].name, processname);
        printf("%d\n", pid);
    }
}

void fg(int cmd_bytes, char command[][50], pid_t termpid)
{
    char *cmdpointers[cmd_bytes];
    pid_t pid;
    int stat;
    int i = 0;
    for (i = 0; i < cmd_bytes; i++)
    {
        cmdpointers[i] = &command[i][0];
    }
    cmdpointers[i] = NULL;
    pid = fork();
    if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(cmdpointers[0], cmdpointers) < 0)
        {
            fprintf(stderr, "Error executing %s command\n", cmdpointers[0]);
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

        strcpy(processname, cmdpointers[0]);
        for (int i = 1; i < cmd_bytes; i++)
        {
            strcat(processname, " ");
            strcpy(processname1, processname);
            sprintf(processname, "%s%s", processname1, cmdpointers[i]);
        }
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(0, pid);
        waitpid(pid, &stat, WUNTRACED);
        tcsetpgrp(0, termpid);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);

        if (WIFSTOPPED(stat))
        {
            array[processcount].pid = pid;
            array[processcount].status = 1;
            strcpy(array[processcount++].name, processname);
        }
    }
}
