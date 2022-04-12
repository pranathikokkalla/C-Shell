#include "main.h"

void signal_ctrlc(int signal)
{
    printf("\n");
    display();
    int state = prompt(homepath);
    if (state == 0)
    {
        return;
    }
    fflush(stdout);
}
void signal_ctrlz(int signal)
{
    /*int val;
    if (fore_status == 1)
    {
        val = kill(fore_pid, SIGTTIN);
        if (val < 0)
        {
            printf("Error in kill process\n");
            return;
        }
        val = kill(fore_pid, SIGTSTP);
        if (val < 0)
        {
            printf("Error in kill process\n");
            return;
        }
        fore_status = 0;
        array[processcount].pid = fore_pid;
        array[processcount].status = 1;
        strcpy(array[processcount++].name, fore_name);
    }*/
    printf("\n");
    display();
    int state = prompt(homepath);
    if (state == 0)
    {
        return;
    }
    fflush(stdout);
}
