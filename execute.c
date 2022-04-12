#include "main.h"

void execute(int pipecmd_bytes, pid_t termpid, char *path, char pipecommand[][50])
{
    int i, j, flag = 0;
    for (j = 0; j < pipecmd_bytes; j++)
    {
        if (!strcmp(pipecommand[j], "&"))
        {
            flag = 1;
            break;
        }
    }
    int redir = 0;
    for (j = 0; j < pipecmd_bytes; j++)
    {
        if (strcmp(pipecommand[j], "<") == 0 || strcmp(pipecommand[j], ">") == 0 || strcmp(pipecommand[j], ">>") == 0)
        {
            redir = 1;
            break;
        }
    }
    if (redir == 1)
    {
        redirect(pipecmd_bytes, pipecommand);
    }
    if (flag == 1)
    {
        bg(pipecmd_bytes, pipecommand, termpid);
    }
    else if (strcmp(pipecommand[0], "echo") == 0)
    {
        echo(pipecmd_bytes, pipecommand);
    }
    else if (strcmp(pipecommand[0], "cd") == 0)
    {
        if (pipecmd_bytes > 2)
        {
            printf("Too many arguments to handle\n");
            return;
        }
        strcpy(path, change_dir(pipecmd_bytes, pipecommand, homepath, path));
    }
    else if (strcmp(pipecommand[0], "pwd") == 0)
    {
        pwd();
    }
    else if (strcmp(pipecommand[0], "ls") == 0)
    {
        ls(pipecmd_bytes, pipecommand, homepath);
    }
    else if (strcmp(pipecommand[0], "pinfo") == 0)
    {
        pinfo(pipecmd_bytes, pipecommand, homepath, redir);
    }
    else if (strcmp(pipecommand[0], "jobs") == 0)
    {
        jobs(pipecmd_bytes, pipecommand, redir);
    }
    else if (strcmp(pipecommand[0], "sig") == 0)
    {
        sig(pipecmd_bytes, pipecommand);
    }
    else if (strcmp(pipecommand[0], "fg") == 0)
    {
        foreground(pipecmd_bytes, pipecommand, termpid);
    }
    else if (strcmp(pipecommand[0], "bg") == 0)
    {
        background(pipecmd_bytes, pipecommand);
    }
    else
    {
        if (redir == 1)
            fg1(pipecmd_bytes, termpid, pipecommand);
        else
            fg(pipecmd_bytes, pipecommand, termpid);
    }
}