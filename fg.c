int tokenise(char *inp,char tokens[100][1024],char *delim);
void kjob(char *inp);
//void ctrlZ(int sig);

void fg(char *inp)
{
	char delim[] = " \t\r\n\v\f";
    char tokens[100][1024];
    int a = tokenise(inp,tokens,delim);

    if(a<1 || a>1)
    {
    	printf("\033[1;31mIncorrect number of arguments.\033[0m :(\n");
    }
    else if(atoi(inp)>curi)
    {
    	printf("\033[1;31mInvalid Job number.\033[0m :(\n");
    }
    else
    {
		int num = atoi(inp);
		// char tempi[1024];
		// strcpy(tempi,inp);
		// strcat(tempi," 19");
		// kjob(tempi);
		char temp[1024];
		strcpy(temp,commandcnt[num-1]);
		int x = pidsave[num-1];
		curfg = x;
		for(int i=0;i<curi;i++)
		{
		 		if(i+1==num)
		 		{
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
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN); 
		tcsetpgrp(STDIN_FILENO,x);
		kill(x,SIGCONT);
		int status;
		waitpid(x, &status, WUNTRACED);
		tcsetpgrp(STDIN_FILENO, getpgrp());
		signal(SIGTTIN, SIG_DFL); 
		signal(SIGTTOU, SIG_DFL);
		//signal(SIGTSTP,ctrlZ);

		if(WIFSTOPPED(status))
		{
			printf("\033[01;33m	%s with PID %d pushed to background \033[0;31m\n",temp,x);
		//	strcpy(jobs[back].job_name, CURR_JOB);
			strcpy(commandcnt[curi],temp);
			pidsave[curi]=x;
			curi++;

        	//jobs[back_g].PID = CHILD_ID;
        	//back_g++;
		} 

}
}
