# default : main

# main :  headers.h functions.h tokenise.c trimSpace.c cdCommand.c lsCommand.c pinfo.c sysCommands.c history.c redirection.c execute.c envar.c piping.c main.c 
# 		gcc tokenise.c trimSpace.c cdCommand.c lsCommand.c pinfo.c sysCommands.c history.c redirection.c execute.c envar.c piping.c main.c -o shell

all:
	gcc -o shell main.c