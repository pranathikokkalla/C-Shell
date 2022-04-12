#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <grp.h>
#include <signal.h>
#include <sys/wait.h>
#include <assert.h>

void display();
void checkhostname(int x);
void echo(int cmd_bytes, char command[][50]);
int redirect(int cmd_bytes, char command[][50]);
void red(int cmd_bytes, char command[][50], char *new_cmd);
char *change_dir(int cmd_bytes, char command[][50], char *homepath, char *olddir);
int prompt(char *homepath);
void pwd();
void ls(int cmd_bytes, char command[][50], char *homepath);
void print(char filepath[], char *file);
void total();
void pinfo(int cmd_bytes, char command[][50], char *homepath, int redir);
void jobs(int cmd_bytes, char command[][50], int redir);
void sig(int cmd_bytes, char command[][50]);
void foreground(int cmd_bytes, char command[][50], pid_t termpid);
void background(int cmd_bytes, char command[][50]);
void signals(int signal);
void fg(int cmd_bytes, char command[][50], pid_t termpid);
void fg1(int cmd_bytes, pid_t termpid, char command[][50]);
void bg(int cmd_bytes, char command[][50], pid_t termpid);
void signal_ctrlc(int signal);
void signal_ctrlz(int signal);

void execute(int pipecmd_bytes, pid_t termpid, char *path, char pipecommand[][50]);
void piping(int cmd_bytes, char *cmd, pid_t termpid, char *path, char command[][50]);

char *homepath;
int processcount;

typedef struct node node;
typedef struct node *ptrtonode;
struct node
{
    char name[100];
    pid_t pid;
    int status;
};
node array[1024];
int shellin, shellout;
char *cmdpointers1[1024];

#endif