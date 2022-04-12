#include "main.h"

void jobs(int cmd_bytes, char command[][50], int redir)
{
    typedef struct result result;
    struct result
    {
        int ind;
        char name[100];
        char state[10];
        pid_t pid;
    };
    result sort[100];
    int i, j = 0, k, index = 0, count, dummy, b = 0;
    pid_t dummy1;
    char stat[1024], state[10];
    char buffer[100];
    if (cmd_bytes > 2 && redir == 0)
    {
        printf("Too many arguments passed!!\n");
        return;
    }
    
    for (i = 0; i < cmd_bytes; i++)
    {
        if (strcmp(command[i], "") == 0)
        {
            break;
        }
        b++;
    }
    cmd_bytes = b;

    for (i = 0; i < processcount; i++)
    {
        count = 0;
        if (array[i].status == 0)
        {
            continue;
        }
        index++;
        sprintf(stat, "/proc/%d/stat", array[i].pid);
        FILE *fp = fopen(stat, "r");
        if (fp == NULL)
        {
            printf("Could not open the file\n");
            return;
        }
        char temp;
        fscanf(fp, "%*d %*s %c", &temp);
        if (temp == 'T' || temp == 't')
        {
            strcpy(state, "Stopped");
        }
        else
        {
            strcpy(state, "Running");
        }
        if (cmd_bytes == 1)
        {
            sort[j].ind = index;
            strcpy(sort[j].state, state);
            strcpy(sort[j].name, array[i].name);
            sort[j].pid = array[i].pid;
            j++;
        }
        else if (strcmp(command[1], "-r") == 0 && strcmp(state, "Running") == 0)
        {
            sort[j].ind = index;
            strcpy(sort[j].state, state);
            strcpy(sort[j].name, array[i].name);
            sort[j].pid = array[i].pid;
            j++;
        }
        else if (strcmp(command[1], "-s") == 0 && strcmp(state, "Stopped") == 0)
        {
            sort[j].ind = index;
            strcpy(sort[j].state, state);
            strcpy(sort[j].name, array[i].name);
            sort[j].pid = array[i].pid;
            j++;
        }
        // printf("%s%s\n", command[1], state);
    }
    for (i = 0; i < j; i++)
    {
        for (k = i + 1; k < j; k++)
        {
            if (strcmp(sort[i].name, sort[k].name) > 0)
            {
                strcpy(buffer, sort[i].name);
                strcpy(sort[i].name, sort[k].name);
                strcpy(sort[k].name, buffer);

                strcpy(buffer, sort[i].state);
                strcpy(sort[i].state, sort[k].state);
                strcpy(sort[k].state, buffer);

                dummy = sort[i].ind;
                sort[i].ind = sort[k].ind;
                sort[k].ind = dummy;

                dummy1 = sort[i].pid;
                sort[i].pid = sort[k].pid;
                sort[k].pid = dummy1;
            }
        }
    }
    for (i = 0; i < j; i++)
    {
        printf("[%d] %s %s [%d]\n", sort[i].ind, sort[i].state, sort[i].name, sort[i].pid);
    }
}

void sig(int cmd_bytes, char command[][50])
{
    int i, index = 0, f = 1, index1 = 0;
    if (cmd_bytes != 3)
    {
        printf("Number of arguments passed are %d\n", cmd_bytes);
        return;
    }
    int arg1, arg2, retval;
    arg1 = atoi(command[1]);
    arg2 = atoi(command[2]);
    for (i = 0; i < processcount; i++)
    {
        if (array[i].status == 0)
        {
            continue;
        }
        index++;
        if (index == arg1)
        {
            retval = kill(array[i].pid, arg2);
            if (retval == -1)
            {
                printf("Error in kill process\n");
                return;
            }
            else if (retval == 0)
            {
                array[i].status = 0;
            }
            break;
        }
        index1++;
    }
    if (index1 == processcount)
    {
        printf("No such process exists\n");
    }
}

void foreground(int cmd_bytes, char command[][50], pid_t termpid)
{
    int i, index = 0, index1 = 0;
    if (cmd_bytes > 2 || cmd_bytes < 2)
    {
        printf("The number of arguments are %d\n", cmd_bytes);
        return;
    }
    for (i = 0; i < processcount; i++)
    {
        if (array[i].status == 0)
        {
            continue;
        }
        index++;
        int arg1, retval;
        arg1 = atoi(command[1]);
        int stat;
        if (index == arg1)
        {
            retval = kill(array[i].pid, SIGCONT);
            if (retval == -1)
            {
                printf("Error in kill process\n");
                return;
            }
            else if (retval == 0)
            {
                array[i].status = 0;
                signal(SIGTTOU, SIG_IGN);
                signal(SIGTTIN, SIG_IGN);
                tcsetpgrp(0, array[i].pid);
                waitpid(array[i].pid, &stat, WUNTRACED);
                tcsetpgrp(0, termpid);
                signal(SIGTTOU, SIG_DFL);
                signal(SIGTTIN, SIG_DFL);

                if (WIFSTOPPED(stat))
                {
                    array[processcount].pid = array[i].pid;
                    array[processcount].status = 1;
                    strcpy(array[processcount++].name, "fg");
                }
            }
            break;
        }
        index1++;
    }
    if (index1 == processcount)
    {
        printf("No such process exists\n");
    }
}

void background(int cmd_bytes, char command[][50])
{
    int i, index = 0, index1 = 0;
    if (cmd_bytes > 2 || cmd_bytes < 2)
    {
        printf("The number of arguments are %d\n", cmd_bytes);
        return;
    }
    for (i = 0; i < processcount; i++)
    {
        if (array[i].status == 0)
        {
            continue;
        }
        index++;
        int arg1, retval1, retval2;
        arg1 = atoi(command[1]);
        if (index == arg1)
        {
            retval1 = kill(array[i].pid, SIGTTIN);
            if (retval1 == -1)
            {
                printf("Error in kill process\n");
                return;
            }
            retval2 = kill(array[i].pid, SIGCONT);
            if (retval2 == -1)
            {
                printf("Error in kill process\n");
                return;
            }
            break;
        }
        index1++;
    }
    if (index1 == processcount)
    {
        printf("No such process exists\n");
    }
}
