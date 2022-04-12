#include "main.h"

void pinfo(int cmd_bytes, char command[][50], char *homepath, int redir)
{
    pid_t pid;
    int cmp, count = 1;
    char stat[1024], buff[1024], status[5], a[1024], b[1024];
    if (cmd_bytes == 1)
    {
        pid = getpid();
    }
    else if (cmd_bytes == 2)
    {
        pid = atoi(command[1]);
    }
    else if (redir == 0)
    {
        printf("Too many arguments passed!!\n");
        return;
    }
    printf("pid -- %d\n", pid);
    printf("Process Status -- ");
    sprintf(stat, "/proc/%d/stat", pid);
    FILE *fp = fopen(stat, "r");
    if (fp == NULL)
    {
        printf("Could not open the file\n");
        return;
    }
    pid_t pgrp, tpgid;
    long int size, vm;
    while (fscanf(fp, "%s", buff) == 1)
    {
        if (count == 3)
            strcpy(status, buff);
        if (count == 5)
            pgrp = atoi(buff);
        if (count == 8)
            tpgid = atoi(buff);
        if (count == 23)
            vm = atoi(buff);
        count++;
    }
    if (tpgid == pgrp)
    {
        cmp = 1;
    }
    else
    {
        cmp = 0;
    }
    printf("{%s", status);
    if (cmp == 1)
        printf("+");
    printf("}\n");
    printf("memory -- %ld bytes {Virtual Memory}\n", vm);
    sprintf(a, "/proc/%d/exe", pid);
    size = readlink(a, b, 1024);
    if (size < 0)
    {
        printf("Error in opening the file %s\n", a);
        return;
    }
    b[size] = 0;
    printf("Executable Path -- ");
    if (strstr(b, homepath))
    {
        printf("~");
        char buffer[200];
        sprintf(buffer, "%s", b + strlen(homepath));
        printf("%s\n", buffer);
    }
    else
    {
        printf("%s\n", b);
    }
}