#include "main.h"

void signals(int signal)
{
    int stat;
    pid_t pid = waitpid(-1, &stat, WNOHANG);

    for (int i = 0; i < processcount; i++)
    {
        if ((array[i].pid == pid) && WIFEXITED(stat))
        {
            if (WEXITSTATUS(stat) != 0)
            {
                printf("\n%s with pid %d exited abnormally\n", array[i].name, pid);
            }
            else
            {
                printf("\n%s with pid %d exited normally\n", array[i].name, pid);
            }
            array[i].status = 0;
            display();
            int state = prompt(homepath);
            fflush(stdout);
            break;
        }
    }
}

