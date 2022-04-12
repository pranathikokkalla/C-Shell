#include "main.h"

int main()
{
    printf("----------Shell execution starts here-------------\n");
    char home[200];
    homepath = getcwd(home, sizeof(home));
    char path[200];
    strcpy(path, "");

    size_t size = 20;
    processcount = 0;
    char *string = (char *)malloc(size);
    int no_of_bytes, cmd_bytes;
    int i, j, k = 0, flag, redir, iter = 1, index = 0, state;

    pid_t termpid;
    termpid = getpid();

    signal(SIGCHLD, signals);
    signal(SIGINT, signal_ctrlc);
    signal(SIGTSTP, signal_ctrlz);

    shellin = dup(0);
    shellout = dup(1);
    char command[50][50];

    while (1)
    {
        display();
        state = prompt(homepath);
        if (state == 0)
        {
            return 0;
        }
        no_of_bytes = getline(&string, &size, stdin);
        if (no_of_bytes < 0)
        {
            printf("Exit\n");
            break;
        }
        else
        {
            char list[50][50];
            char cmd[50];

            char *token = strtok(string, ";\n");
            no_of_bytes = 0;
            while (token != NULL)
            {
                strcpy(list[no_of_bytes], token);
                no_of_bytes++;
                token = strtok(NULL, ";\n");
            }
            for (i = 0; i < no_of_bytes; i++)
            {
                flag = 0;
                strcpy(cmd, list[i]);
                token = strtok(list[i], " \t");
                cmd_bytes = 0;
                while (token != NULL)
                {
                    strcpy(command[cmd_bytes], token);
                    cmd_bytes++;
                    token = strtok(NULL, " \t");
                }
                if (strcmp(command[0], "exit") == 0)
                    return 0;
                if (strstr(cmd, "|"))
                {
                    piping(cmd_bytes, cmd, termpid, path, command);
                }
                else
                {
                    for (j = 0; j < cmd_bytes; j++)
                    {
                        if (!strcmp(command[j], "&"))
                        {
                            flag = 1;
                            break;
                        }
                    }
                    redir = 0;
                    for (j = 0; j < cmd_bytes; j++)
                    {
                        if (strcmp(command[j], "<") == 0 || strcmp(command[j], ">") == 0 || strcmp(command[j], ">>") == 0)
                        {
                            redir = 1;
                            break;
                        }
                    }
                    if (strcmp(command[0], "repeat") == 0)
                    {
                        iter = atoi(command[1]);
                        for (j = 2; j < cmd_bytes; j++)
                        {
                            strcpy(command[j - 2], command[j]);
                        }
                        cmd_bytes = cmd_bytes - 2;
                    }
                    while (iter)
                    {
                        if (redir == 1)
                        {
                            int redirect_return = redirect(cmd_bytes, command);
                            if (redirect_return == 0)
                            {
                                break;
                            }
                        }
                        if (flag == 1)
                        {
                            bg(cmd_bytes, command, termpid);
                        }
                        else if (strcmp(command[0], "echo") == 0)
                        {
                            echo(cmd_bytes, command);
                        }
                        else if (strcmp(command[0], "cd") == 0)
                        {
                            if (cmd_bytes > 2 && redir == 0)
                            {
                                printf("Too many arguments to handle\n");
                                continue;
                            }
                            strcpy(path, change_dir(cmd_bytes, command, homepath, path));
                        }
                        else if (strcmp(command[0], "pwd") == 0)
                        {
                            pwd();
                        }
                        else if (strcmp(command[0], "ls") == 0)
                        {
                            ls(cmd_bytes, command, homepath);
                        }
                        else if (strcmp(command[0], "pinfo") == 0)
                        {
                            pinfo(cmd_bytes, command, homepath, redir);
                        }
                        else if (strcmp(command[0], "jobs") == 0)
                        {
                            jobs(cmd_bytes, command,redir);
                        }
                        else if (strcmp(command[0], "sig") == 0)
                        {
                            sig(cmd_bytes, command);
                        }
                        else if (strcmp(command[0], "fg") == 0)
                        {
                            foreground(cmd_bytes, command, termpid);
                        }
                        else if (strcmp(command[0], "bg") == 0)
                        {
                            background(cmd_bytes, command);
                        }
                        else
                        {
                            if (redir == 1)
                                fg1(cmd_bytes, termpid, command);
                            else
                                fg(cmd_bytes, command, termpid);
                        }
                        dup2(shellin, 0);
                        dup2(shellout, 1);
                        iter--;
                    }
                }
                iter = 1;
                for (j = 0; j < cmd_bytes; j++)
                {
                    strcpy(command[j], "");
                }
            }
        }
    }
    return 0;
}