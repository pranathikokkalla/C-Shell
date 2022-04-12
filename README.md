File descriptions:

<b>main.h:</b> This file contains the libraries that are used in this assignment.It also contains some global variable declarations and struct declarations. All other .c files are linked with this file.

<b>main.c :</b> This file is the main file for this shell execution. It finds the host name and the username. It runs a loop to read the input given by user. There can be multiple commands in a single line seperated by ; and there can aslo be multiple spaces in a command. This file handles them by using strtok. It processes each command in the given order and calls the suitable function.
It also enables the repeat command, which is used to repeat a process required number of times. It also implements the ctrl C, ctrl D and ctrl Z signals.
When the input given is ctrl D, the getline function returns -1 and the program exits.

<b>display.c:</b> It prints the user name and the host name in the required format. It finds out the current working directory and prints it in a suitable way.

<b>cd.c :</b> This file contains the implementation of the cd command used to change directories in linux.
cd commands that are implemented are:
1) cd
2) cd ~
3) cd ..
4) cd -
5) cd < directorypath >
6) cd .

<b>inbuilt.c:</b> This file contains the implementation of the inbuilt commands echo and pwd.

<b>ls.c:</b> This file cntains the implementation of the command ls. The two flags of this command, -l and -a are also implemented. The flags can be in any combination and there can also be multiple direcories or files given as inputs. This file prints the content of the input directories and files accordingly.

ls commands that are implemented are:
1) ls
2) ls ~
3) ls ..
4) ls .
5) ls -a
6) ls -l
7) ls -al / ls -la 
8) The ls command can also be provided with multiple arguments in the same command

<b>fb.c :</b> This file contains the implementation of the back ground and fore ground processes. Back ground processes have & at the end of their command. When a back ground process is executed pid of that process wull be printed along with the execution. For a foreground process no pid will be printed. If a foreground process is interrupted by ctrl Z signal, then the foreground process turns into background.

Some of the background and the foreground processes that can be implemented are: 
1) gedit & and gedit
2) vi & and vi
3) date & and date
4) sleep no_of_seconds & and sleep no_of_seconds

<b>pinfo.c :</b> This file contains the implementation of the command 'pinfo' that is defined by user. This command gives the process information of the current process if no pid is given. If some pid is given then the process info of the process with tthat pid will be printed.

<b>signal.c :</b> This file contains the implementation of the statement that is to be printed when a back ground process terminates. It prints the way in which the child back ground process has been exited. After receving the signal it prints normally if the process exited normally else it prints abnormally if the process exits abnormally.

<b> redirect.c : </b> This file contains the implementation of the redirection functionality of the given input. It uses the function dup2() for this. It also creates the output file with permissions 0644. 

<b> exec.c : </b> This file contains the function void <b>fg1(int cmd_bytes, pid_t termpid,char command[][50])</b>, which implements the foreground process of the input command.

<b> pipe.c : </b> This file contains the implementation of the pipe functionality in the commands. In this function, the command is parsed (tokenized) with | and each of the subseuqent commands is run in the sequence such that output of the this command becomes the input of the next command.

<b> execute.c : </b> This file contains the execution of all the commands. Tthe command is checked with the given inbuilt commands and calls the corresponding function.

<b> jobs.c : </b> This file conatins the implementation of some inbuilt commands like jobs, sig,fg and bg. The function jobs contains the execution of this command. It prints out all the current background processes. jobs -r is also implemented which displays only those background jobs whose state is running. jobs -s is also implemented which displays only those background jobs whose state is stopped. The display is sorted according to the names of the processes.

The function sig implements the inbuilt command sig index_num signal_num. This command sends the signal signal_num to the background process having index_num as it's job number.

The function foreground implements the inbuilt command fg job_number. This command brings the running or stopped background job corresponding to ​job_number​ to the foreground, and changes its state to ​running. It throws an error if no such back ground process exist with the given job_number.

The function background implements the inbuilt command bg job_number. This command Changes the state of a stopped background job to running (in the background).
It throws an error if no such back ground process exist with the given job_number.

<b> ctrl.c: </c> This contains the implementation of two signals ctrl C and ctrl Z. signal_ctrlc is the function which executes ctrl C signal. It interrupts any currently running fore ground process by sending SIGINT signal.

signal_ctrlz is the function which executes ctrl Z signal. It pushes any currently runnning foreground process to background and the state of the process is changes from running to stopped.

<b>makefile :</b> This file has the code required to compile the shell. On entering ./a.out the shell will be executed.

