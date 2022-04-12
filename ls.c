#include "main.h"
void total1(DIR *dir, struct dirent *directory, char filepath1[], int sample)
{
    long sum = 0;
    char filepath[1000];
    struct stat st;
    while ((directory = readdir(dir)) != NULL)
    {
        strcpy(filepath, filepath1);
        strcat(filepath, "/");
        strcat(filepath, directory->d_name);
        if (stat(filepath, &st) == 0)
        {
            if (sample == 0)
            {
                if (directory->d_name[0] != '.')
                    sum = sum + st.st_blocks;
            }
            else
                sum = sum + st.st_blocks;
        }
    }
    printf("total %ld\n", sum / 2);
    rewinddir(dir);
}
void print(char filepath[], char *file)
{
    struct stat filestat;
    if (stat(filepath, &filestat) >= 0)
    {
        char time[80];
        char timer[80];
        char year[5];
        char month[10];
        time_t time1 = filestat.st_mtime;
        struct tm buf;
        struct passwd *passwd = getpwuid(filestat.st_uid);
        struct group *group = getgrgid(filestat.st_gid);
        localtime_r(&time1, &buf);
        printf("%c", S_ISDIR(filestat.st_mode) ? 'd' : '-');
        printf("%c", (filestat.st_mode & S_IRUSR) ? 'r' : '-');
        printf("%c", (filestat.st_mode & S_IWUSR) ? 'w' : '-');
        printf("%c", (filestat.st_mode & S_IXUSR) ? 'x' : '-');
        printf("%c", (filestat.st_mode & S_IRGRP) ? 'r' : '-');
        printf("%c", (filestat.st_mode & S_IWGRP) ? 'w' : '-');
        printf("%c", (filestat.st_mode & S_IXGRP) ? 'x' : '-');
        printf("%c", (filestat.st_mode & S_IROTH) ? 'R' : '-');
        printf("%c", (filestat.st_mode & S_IWOTH) ? 'W' : '-');
        printf("%c  ", (filestat.st_mode & S_IXOTH) ? 'x' : '-');
        strftime(time, sizeof time, "%b %d %H:%M", &buf);
        strftime(year, sizeof year, "%Y", &buf);
        strftime(month, sizeof month, "%M", &buf);
        strftime(timer, sizeof time, "%b %d %Y", &buf);
        if (strcmp(year, "2021") < 0)
        {
            printf("%3ld %s %s %11ld %s %s\n", filestat.st_nlink, passwd->pw_name, group->gr_name, filestat.st_size, timer, file);
        }
        else if (strcmp(month, "Jan") == 0)
            printf("%3ld %s %s %11ld %s %s\n", filestat.st_nlink, passwd->pw_name, group->gr_name, filestat.st_size, timer, file);
        else if (strcmp(month, "Feb") == 0)
            printf("%3ld %s %s %11ld %s %s\n", filestat.st_nlink, passwd->pw_name, group->gr_name, filestat.st_size, timer, file);
        else if (strcmp(month, "Mar") == 0)
            printf("%3ld %s %s %11ld %s %s\n", filestat.st_nlink, passwd->pw_name, group->gr_name, filestat.st_size, timer, file);
        else
            printf("%3ld %s %s %11ld %s %s\n", filestat.st_nlink, passwd->pw_name, group->gr_name, filestat.st_size, time, file);
    }
    else
    {
        perror("Error!!!!");
    }
}

void ls(int cmd_bytes, char command[][50], char *homepath)
{
    char currpath[1000];
    char *path;
    char filepath[1000];
    char filepath1[1000];
    path = getcwd(currpath, sizeof(currpath)); /* get current working dir*/
    struct dirent **namelist;
    int n, i, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count = 0;
    struct stat statbuf;
    for (i = 0; i < cmd_bytes; i++)
    {
        if (strcmp(command[i], "") == 0)
        {
            break;
        }
        count++;
    }
    cmd_bytes = count;
    for (i = 1; i < cmd_bytes; i++)
    {
        if (strcmp(command[i], "-a") == 0)
        {
            count1++;
        }
        if (strcmp(command[i], "-l") == 0)
        {
            count2++;
        }
        if (strcmp(command[i], "-al") == 0)
        {
            count3++;
        }
        if (strcmp(command[i], "-la") == 0)
        {
            count4++;
        }
    }
    count = cmd_bytes - count1 - count2 - count3 - count4 - 1;
    if (cmd_bytes == 1)
    {
        n = scandir(path, &namelist, NULL, alphasort);
        if (n < 0)
        {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        else
        {
            while (n--)
            {
                if (namelist[n]->d_name[0] != '.')
                    printf("%s\n", namelist[n]->d_name);
                free(namelist[n]);
            }
            free(namelist);
        }
        return;
    }
    else if (!count && count1 && !count2 && !count3 && !count4)
    {
        n = scandir(path, &namelist, NULL, alphasort);
        if (n < 0)
        {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        else
        {
            while (n--)
            {
                printf("%s\n", namelist[n]->d_name);
                free(namelist[n]);
            }
            free(namelist);
        }
        return;
    }
    else if (!count && !count1 && count2 && !count3 && !count4)
    {
        struct dirent *directory;
        DIR *dir;
        dir = opendir(currpath);
        if (dir == NULL)
        {
            perror("No such directory found");
            return;
        }
        total1(dir, directory, currpath, 0);
        while ((directory = readdir(dir)) != NULL)
        {
            strcpy(filepath, currpath);
            strcat(filepath, "/");
            strcat(filepath, directory->d_name);
            if (directory->d_name[0] != '.')
                print(filepath, directory->d_name);
        }
        return;
    }
    else if (!count && ((count1 && count2) || count3 || count4))
    {
        struct dirent *directory;
        DIR *dir;
        dir = opendir(currpath);
        if (dir == NULL)
        {
            perror("No such directory found");
            return;
        }
        total1(dir, directory, currpath, 1);
        while ((directory = readdir(dir)) != NULL)
        {
            strcpy(filepath, currpath);
            strcat(filepath, "/");
            strcat(filepath, directory->d_name);
            print(filepath, directory->d_name);
        }
        return;
    }

    if (count1 && !count2 && !count3 && !count4)
    {
        for (i = 1; i < cmd_bytes; i++)
        {
            if (strcmp(command[i], "-a") != 0)
            {
                if (strstr(command[i], "~"))
                {
                    char *name = command[i];
                    name++;
                    strcpy(filepath1, homepath);
                    strcat(filepath1, name);
                }
                else
                {
                    strcpy(filepath1, command[i]);
                }
                n = scandir(filepath1, &namelist, NULL, alphasort);
                if (n < 0)
                {
                    if (stat(filepath1, &statbuf) != 0)
                    {
                        perror("Error");
                        continue;
                    }
                    printf("%s\n", filepath1);
                    continue;
                }
                if (count > 1)
                {
                    printf("%s:\n", filepath1);
                }
                while (n--)
                {
                    printf("%s\n", namelist[n]->d_name);
                    free(namelist[n]);
                }
                free(namelist);
            }
        }
    }
    else if (!count1 && !count2 && !count3 && !count4)
    {
        for (i = 1; i < cmd_bytes; i++)
        {
            if (strstr(command[i], "~"))
            {
                char *name = command[i];
                name++;
                strcpy(filepath1, homepath);
                strcat(filepath1, name);
            }
            else
            {
                strcpy(filepath1, command[i]);
            }
            n = scandir(filepath1, &namelist, NULL, alphasort);
            if (n < 0)
            {
                if (stat(filepath1, &statbuf) != 0)
                {
                    perror("Error");
                    continue;
                }
                printf("%s\n", filepath1);
                continue;
            }
            if (count > 1)
            {
                printf("%s:\n", filepath1);
            }
            while (n--)
            {
                if (namelist[n]->d_name[0] != '.')
                    printf("%s\n", namelist[n]->d_name);
                free(namelist[n]);
            }
            free(namelist);
        }
    }
    else if (!count1 && count2 && !count3 && !count4)
    {
        struct dirent *directory;
        DIR *dir;
        for (int i = 1; i < cmd_bytes; i++)
        {
            if (strcmp(command[i], "-l") == 0)
                continue;
            if (strstr(command[i], "~"))
            {
                char *name = command[i];
                name++;
                strcpy(filepath1, homepath);
                strcat(filepath1, name);
            }
            else
            {
                strcpy(filepath1, command[i]);
            }
            dir = opendir(filepath1);
            if (dir == NULL)
            {
                if (stat(filepath1, &statbuf) != 0)
                {
                    perror("Error");
                    continue;
                }
                print(filepath1, filepath1);
                continue;
            }
            if (count > 1)
            {
                printf("%s:\n", filepath1);
            }
            total1(dir, directory, filepath1, 0);
            while ((directory = readdir(dir)) != NULL)
            {
                strcpy(filepath, filepath1);
                strcat(filepath, "/");
                strcat(filepath, directory->d_name);
                if (directory->d_name[0] != '.')
                    print(filepath, directory->d_name);
            }
        }
    }

    else if ((count1 && count2) || count3 || count4)
    {
        struct dirent *directory;
        DIR *dir;
        for (int i = 1; i < cmd_bytes; i++)
        {
            if ((strcmp(command[i], "-a") == 0) || (strcmp(command[i], "-l") == 0) || (strcmp(command[i], "-al") == 0) ||
                (strcmp(command[i], "-la") == 0))
                continue;
            if (strstr(command[i], "~"))
            {
                char *name = command[i];
                name++;
                strcpy(filepath1, homepath);
                strcat(filepath1, name);
            }
            else
            {
                strcpy(filepath1, command[i]);
            }
            dir = opendir(filepath1);
            if (dir == NULL)
            {
                if (stat(filepath1, &statbuf) != 0)
                {
                    perror("Error");
                    continue;
                }
                print(filepath1, filepath1);
                continue;
            }
            if (count > 1)
            {
                printf("%s:\n", filepath1);
            }
            total1(dir, directory, filepath1, 1);
            while ((directory = readdir(dir)) != NULL)
            {
                strcpy(filepath, filepath1);
                strcat(filepath, "/");
                strcat(filepath, directory->d_name);
                print(filepath, directory->d_name);
            }
        }
    }
}
