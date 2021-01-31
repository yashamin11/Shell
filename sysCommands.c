int tokenise(char *inp,char tokens[100][1024],char *delim);
void trim(char *inp);

void process_terminated(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1,&status,WNOHANG);
	for(int i=0;i<curi;i++)
	{
		if(pid==pidsave[i])
		{
			printf("\033[01;33m\n%s with PID %d exited normally.\033[0m\n",commandcnt[i],pid);
			int j = i;
			for(j=j+1;j<curi;j++)
			{
				pidsave[j-1] =pidsave[j]; 
				strcpy(commandcnt[j-1],commandcnt[j]);
			}
		
			curi--;
			break;
		}
	}
	
	return;
}

void syscom(char *command, char* arg)
{

	char *argv[1024];
	char tokens[100][1024];
	char delim[] = " \t\r\n\v\f";
	int a = tokenise(arg,tokens,delim);
	int i=0,status;
	int j= 1;
	int flag = 0;
	for(i=0;i<a;i++)
	{
		if(strcmp("&",tokens[i])==0)
			{	
				flag = 1;
			}
		else
		{argv[j] = tokens[i];
		j++;}
	}
	argv[0] = command;
	argv[j] = NULL;
	if(flag==1)
	{strcpy(commandcnt[curi],command);
	curi ++;}
	pid_t par = getpid();
	signal(SIGCHLD,process_terminated);
	pid_t child_pid= fork();
	pid_t temp = getpid();

	if(flag==1)
		pidsave[curi-1] =child_pid;

	if(child_pid  > 0) {
		
		if(flag==0)
		curfg = child_pid;

		if(flag != 0 )
		{
			printf("[%d] %d\n",curi,child_pid);
		}		
		else
		{
			// signal(SIGTTIN, SIG_IGN);
   //          signal(SIGTTOU, SIG_IGN);
   //          tcsetpgrp(STDIN_FILENO, child_pid);
			pid_t tpid = waitpid(child_pid,&status,WUNTRACED);
			// tcsetpgrp(STDIN_FILENO, getpgrp());
   //          signal(SIGTTIN, SIG_DFL);
   //          signal(SIGTTOU, SIG_DFL);	
   //          if(WIFSTOPPED(status))
   //             {
   //                  printf("%s with PID %d suspended\n", command, child_pid);
   //                  strcpy(commandcnt[curi],command);
   //                  pidsave[curi] = child_pid;
   //                  curi++;
   //             }
		}
	}
	else {

		if(flag==1)
		{
			setpgid(0,0);
		}
		execvp(argv[0], argv);

		printf("\033[1;31mUnknown command\033[0m :(\n");
		//curi--;
		exit(0);		
	}
	
	
}