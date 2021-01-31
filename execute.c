int tokenise(char *inp,char tokens[100][1024],char *delim);
void trim(char *inp);
int cd(char *inp,char *cwd,char *home);
void ls(int flag[26]);
void lscall(char *inp,char tokens[100][1024],char *cwd, char *home);
void process_terminated(int sig);
void pinfo(char *arg,int flag);
void syscom(char *command,char *arg);
void history_upd(char *com1,char *arg,char *home,int flag);
void redirect(char* inp,int flag);
void pipe_com(char *inp);

void execute_com(char * inp)
{
		//printf("%s check\n",inp);
			int redirection=0;
			int out =0;
			char com1[1024];
			char arg[1024];
			char pipe_temp[100][1024];
			int pipe_flag = 0;
			char cwd [1024];
			getcwd(cwd,1024);
			for(int ii=0;ii<1024;ii++)
			{
				if(inp[ii]=='>' || inp[ii]=='<')
					redirection =1;
				if(inp[ii]=='>')
					out=1;
				if(inp[ii]=='|')
					pipe_flag=1;
			}	
			for(int u=0;u<1024;u++)
			{
				com1[u] = '\0';
				arg[u] = '\0';
			}
			trim(inp);
			int i=0;
			while(inp[i]!=' ' && inp[i]!='\t' && inp[i]!='\0')
			{
				com1[i] = inp[i];
				i++;
			}
			com1[i] = '\0';
			while(inp[i]==' ' && inp[i]!='\0')
				i++;
			int j=0;
			while(1)
			{
				if(inp[i]=='\0')
					break;
				arg[j] = inp[i];
				i++;j++;
			}
			arg[j] = '\0';
			trim(arg);
			trim(com1);
			
			if(pipe_flag==1)
			{
				pipe_com(inp);
				//return ;
			}
			else if(redirection==1)
			{
				redirect(inp,out);

			}
			// else if(strcmp("cd",com1)==0)
			// {		
			// 	cd(arg,cwd,home);
			// }
			
			// else if(strcmp("pwd",com1)==0)
			// {
			// 	printf("%s\n",cwd);
			// }
			else if(strcmp("echo",com1)==0)
			{
				char tokens[100][1024];
				char delim[] = " \t\r\n\v\f";
				tokenise(arg,tokens,delim);
			
				for(i=0;i<100;i++)
				{
					if(tokens[i][0]=='\0')
						break;
					else
					{	
						trim(tokens[i]);
						printf("%s",tokens[i]);
					}
					printf(" ");
				}
				printf("\n");
			}
			// else if(strcmp("ls",com1)==0)
			// {
			// 	char tokens[100][1024];
			// 	tokenise(arg,tokens,delim);
			// 	 for(i=0;i<8;i++)
			// 	{
			// 		if(tokens[i][0]!='\0')
			// 		{
			// 			trim(tokens[i]);
			// 		}
			// 		else
			// 			break;
			// 	}
			// 	lscall(arg,tokens,cwd,home);
			// 	//printf("hey\n");
			// }
			else if(strcmp("pinfo",com1)==0)
			{
				char tokens[100][1024];
				char delim[] = " \t\r\n\v\f";
				tokenise(arg,tokens,delim);
				if(arg[0]!='\0')
				{
					pinfo(arg,1);
				}
				else
				{
					char temp[10];
					pid_t pid = getpid();
					snprintf(temp,10,"%d",pid);
					strcpy(arg,temp);
					pinfo(arg,0);
				}
			}
			// else if(strcmp("history",com1)==0)
			// {
			// 	trim(arg);
			// 	history_upd(com1,arg,home,1);
			// 	continue;

			// }
			else
			{
				syscom(com1,arg);
			}
			
		
	}