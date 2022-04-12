#include "main.h"

void checkhostname(int x)
{
    if (x == -1)
    {
        perror("gethostname");
        exit(1);
    }
}
void display()
{
    char buf[100], hostname[100];
    char *buffer = &buf[0];
    int x;
    buffer = getenv("USER");
    printf("%s", buffer);
    x = gethostname(hostname, sizeof(hostname));
    checkhostname(x);
    printf("@%s:", hostname);
}
int prompt(char *homepath)
{
    char olddir[200];
    char *old = getcwd(olddir, sizeof(olddir));
    if (old != NULL)
    {
        if (strstr(olddir, homepath))
        {
            printf("~");
            char buffer[200];
            sprintf(buffer, "%s", olddir + strlen(homepath));
            printf("%s$", buffer);
        }
        else
        {
            printf("%s$", olddir);
        }
        return 1;
    }
    else
    {
        perror("getcwd() error");
        return 0;
    }
}