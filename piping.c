int tokenise(char *inp,char tokens[100][1024],char *delim);
void trim(char *inp);
void execute_com(char * inp);


void pipe_com(char *inp)
{
	char pipe_tokens[100][1024];
	int a = tokenise(inp,pipe_tokens,"|");
	int i,j,k=0;
	
	//printf("%d\n",x);
	for(i=0;i<a;i++)
	{
		trim(pipe_tokens[i]);
		
		char tokens[100][1024];
		char delim[] = " \t\r\n\v\f";
		// int b = tokenise(pipe_tokens[i],tokens,delim);
		//  printf("%s\n",pipe_tokens[i]);
		// char *argv[1024];
		// for(j=0;j<b;j++)
		// {
		// 	trim(tokens[j]);
		// 	argv[j]=tokens[j];
		// }
		// argv[j] = NULL;
		int pip[2];
		
		pipe(pip);
		//printf("%d %d\n",pip[0],pip[1]);
		pid_t child_pid;
		child_pid = fork();
		

		if(child_pid>0)
		{						
			//int status=0;
			wait(NULL);
			close(pip[1]);	
			k = pip[0];
			//printf("%d hey\n",k);
		}
		else
		{
			//printf("dsfg\n");
			dup2(k,0);
			if(i!=a-1)
			{
				dup2(pip[1],1);
			}
			//close(pip[1]);
			//printf("dsfdds\n");
			//close(1);
			//execvp(argv[0],argv);
			//printf("hey\n");
			execute_com(pipe_tokens[i]);
			//printf("\033[1;31mUnknown command\033[0m :(\n");
			 //close(pip[0]);
			
			exit(0);

		}


	}

	for(i=0;i<1024;i++)
	{
		inp[i]='\0';
	}



}