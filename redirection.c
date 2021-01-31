//#include "./functions.h"
int tokenise(char *inp,char tokens[100][1024],char *delim);
void trim(char *inp);

void redirect(char *inp,int flag)
{
	if(flag==0)
	{
		char tokens[100][1024];
		int a = tokenise(inp,tokens,"<");
		char *argv[1024];
		int k = 0;
		int i;
		for( i=0;i<a;i++)
		{
			if(tokens[i][0]=='\0')
				break;
			else
			{
				trim(tokens[i]);
				argv[i] = tokens[i];
			}
			//printf("%s\n",tokens[i]);
		}
		argv[i] = NULL;

		pid_t child_pid;
		child_pid = fork();

		if(child_pid  > 0)
		{
				pid_t tpid = waitpid(child_pid,&k,0);	
		}
		else 
		{		
			execvp(argv[0], argv);
			printf("\033[1;31mUnknown command\033[0m :(\n");
			exit(0);
		}
	}
	else
	{
		int i=0,j=0;
		char temp[1024];
		char tokens[100][1024],tokens1[100][1024];
		char *argv[1024];
		while(inp[i]!='\0')
		{
			if(inp[i]=='<')
				{
					i++;
					continue;
				}
			else
			{
				temp[j]=inp[i];
				i++;j++;
			}
		}
		temp[j] = '\0';
		int fl = 0,k=0;
		for(i=0;i<j-1;i++)
		{
			if(temp[i]=='>' && temp[i+1]=='>')
				fl=1;
		}
		int a= tokenise(temp,tokens,">");
		char delim[] = " \t\r\n\v\f";
		int b= tokenise(tokens[0],tokens1,delim);
		for(i=0;i<b;i++)
		{
			trim(tokens1[i]);
			argv[i] = tokens1[i];
		}
		argv[i]=NULL;
		for(i=1;i<a;i++)
		{
			trim(tokens[i]);
			//argv[i+b-1] = tokens[i];
			//printf("%s\n",tokens[i]);
		}
		//argv[i+b-1] = NULL;


		pid_t child_pid;
		child_pid = fork();

		if(child_pid  > 0)
		{
				pid_t tpid = waitpid(child_pid,&k,0);	
		}
		else 
		{
			int fd;
			close(1);
			if(fl==1)
			{
				fd = open(tokens[1],O_WRONLY|O_CREAT|O_APPEND,0644);
			}	
			else
			{
				fd = open(tokens[1],O_WRONLY|O_CREAT|O_TRUNC,0644);
			}
			
			//close(fd);	
			execvp(argv[0], argv);
			close(STDOUT_FILENO);
			printf("\033[1;31mUnknown command\033[0m :(\n");
			
			exit(0);
		}
	}
}
