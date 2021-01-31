# Linux Shell

_____________________________________________________________________

## Introduction

This contains details of each command of the shell. 
Multiple commands can be passed as a single argument with colon(;) separation. 

## Commands

1. pwd

	* Displays the name of the current working directory.

2. echo

	* Displays the the string passed as argument.

3. cd 

	* It changes the current working directory to the directory passed as an argument.

	* Implemented in cdCommand.c

4. ls 

	* Displays the list of all files and directories in the specified directory.

	* Flags -l and -a accounted for.

	* Also handles multiple directories as arguments.eg. ls -al dir1 dir2

	* Implemented in lsCommand.c

5. fg and bg processes (System Commands)

	* Is able to run any process in background or foreground.

	* Upon exit(or kill) of a background process ,it displays the name and PID of the killed process.

	* Implemented is sysCommands.c

6. pinfo

	* Displays various information about the process whose PID is passed as an argument.

	* Implemented in pinfo.c

7. history

	* Displays the last 'n'(n<=20) commands exectued by the shell.

	* Also works upon exit and restart of the shell.

	* Implmented in history.c

8. kjob

	* Takes a job ID of a bg process and sends a signal number to that process.

	* Implemented in kjob.c

9. fg & bg

	* fg : Brings a bg process to foreground.

	* bg : Changes state of stopped bg process to running.

10. setenv and unsetenv

	* setenv : Creates or changes the value of an env variable.

	* unsetenv : Destroys the env varialbe.

11. overkill

	* Terminates all the bg process.

12. Input/Output Redirection with Piping

13. Signal Handling

	* Ctrl-D : quits the shell

	* Ctrl-Z : Pushes a fg process to background.

	* Ctrl-C : Interrupts a fg process.
	



## Note :

* The maximum length of a command is restricted to 1024 characters. 

* Maximum no. of commands passed at a time is restricted to 100.

* When a backgorund process is killed and the message is displayed. Press Enter to restore the prompt.




	