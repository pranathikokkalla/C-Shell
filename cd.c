#include "main.h"

char *change_dir(int cmd_bytes, char command[][50], char *homepath, char olddir[])
{
    char *buffer = getenv("USER");
    char buf[1000];
    sprintf(buf, "~%s", buffer);

    char cwd[1000];
    char *path = getcwd(cwd, sizeof(cwd));
    if (cmd_bytes == 1)
    {
        chdir(homepath);
        return path;
    }
    if (strcmp(command[1], "~") == 0)
    {
        chdir(homepath);
        return path;
    }
    if (strcmp(command[1], "-") == 0)
    {
        if (strcmp(olddir, "") == 0)
        {
            perror("OLDPWD not set");
            strcpy(path, "");
            return path;
        }
        else if (chdir(olddir) == -1)
        {
            perror("Error in performing cd:");
        }
        else
        {
            printf("%s\n", olddir);
        }

        return path;
    }
    if (strcmp(command[1], ".") == 0)
    {
        return path;
    }
    if (command[1][0] == '~')
    {
        if (strcmp(command[1], buf) == 0)
        {
            chdir(homepath);
        }
        else
        {
            perror("No such file or directory\n");
        }
        return path;
    }
    else
    {
        if (chdir(command[1]) == -1)
        {
            perror("Error in performing cd operation");
            return olddir;
        }
        return path;
    }
}