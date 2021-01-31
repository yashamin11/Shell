#include "headers.h"
#include "functions.h"

#define ll long long int

//-----------------//
  #define amin main
//-----------------//

int buf = 1024;
char delim[] = " \t\r\n\v\f";
int d=0;



int amin()
{

	char cwd[buf],home[buf],user[buf],host[buf],prompt[1024]="";
	gethostname(host,buf);
	getlogin_r(user,buf);

	getcwd(home,buf);strcpy(cwd,home);
	strcat(user,"@");
	strcat(user,host);

	int flag= 1;
	ll i,j;

	char temp[1024];
	strcpy(temp,home);
	char filehis[]="/history.txt";

	strcat(temp,filehis);
	int fd = open(temp,O_RDWR|O_CREAT,0777);
	int ex= 0;
	//------------Signal
	signal(SIGINT,ctrlC);
	signal(SIGTSTP,ctrlZ);
	//------------
	while(1)
	{
		//fflush(stdin);

		getcwd(cwd,1024);
		if(strcmp(cwd,home)==0 )
		{ 
			d++;
			//if(d==1)
			printf("< \033[1;32m%s\033[0m:\033[1;34m~\033[0m >",user);	
			//strcpy(lastdir,"~");
		}
		else
		{	
			changeflag = 1;
			//printf("%s sad\n",cwd);
			if(strstr(cwd,home)!=NULL)
			{
				char temp[buf],temp1[buf];
				getcwd(cwd,1024);
				strcpy(temp,cwd);
				printf("< \033[1;32m%s\033[0m:\033[1;34m~/\033[0m",user);
				j = strlen(home);
				j++;i=0;
				while(temp[j]!='\0')
					{temp1[i] = temp[j];
				i++;j++;}
				temp1[i]='\0';
				printf("\033[1;34m%s\033[0m > ",temp1);
				char teemp[] = "~/";
				strcat(teemp,temp1);
				
			}
			else
			{
				getcwd(cwd,1024);
				printf("< \033[1;32m%s\033[0m:\033[1;34m%s\033[0m >",user,cwd);
			}

		}
		
		printf(" ");
		
		for(i=0;i<1024;i++)
			maincommand[i]= '\0';
		//printf("%s ch\n",command);
		//if(command[])
		
		 char *tep = fgets(maincommand,buf,stdin);
		 if(tep==NULL)
		 {	printf("\n");
		 	ex=1;
		 }

	
		char temp[100][1024];
	
	maincommand[strlen(maincommand)-1]='\0';
	
		trim(maincommand);
		
		char coms[100][1024];
		ll a = tokenise(maincommand,coms,";");
		
		
		for(ll p =0;p<a;p++)
		{
			//printf("%s\n",coms[p]);
			int redirection=0;
			int out =0;
			char com1[buf];
			char arg[buf];
			char pipe_temp[100][1024];
			int pipe_flag = 0;
			for(int ii=0;ii<1024;ii++)
			{
				if(coms[p][ii]=='>' || coms[p][ii]=='<')
					redirection =1;
				if(coms[p][ii]=='>')
					out=1;
				if(coms[p][ii]=='|')
					pipe_flag=1;
			}	
			for(ll u=0;u<1024;u++)
			{
				com1[u] = '\0';
				arg[u] = '\0';
			}
			trim(coms[p]);
			i=0;
			while(coms[p][i]!=' ' && coms[p][i]!='\t' && coms[p][i]!='\0')
			{
				com1[i] = coms[p][i];
				i++;
			}
			com1[i] = '\0';
			while(coms[p][i]==' ' && coms[p][i]!='\0')
				i++;
			j=0;
			while(1)
			{
				if(coms[p][i]=='\0')
					break;
				arg[j] = coms[p][i];
				i++;j++;
			}
			arg[j] = '\0';
			trim(arg);
			trim(com1);
			
			if(pipe_flag==1)
			{
				pipe_com(coms[p]);
			}
			else if(redirection==1)
			{
				redirect(coms[p],out);
			}
			else if(strcmp("cd",com1)==0)
			{		
				cd(arg,cwd,home);
			}
			else if(strcmp("quit",com1)==0)
			{
				ex = 1;
				break;
				
			}
			else if(strcmp("pwd",com1)==0)
			{
				printf("%s\n",cwd);
			}
			else if(strcmp("echo",com1)==0)
			{
				char tokens[100][1024];
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
			else if(strcmp("ls",com1)==0)
			{
				char tokens[100][1024];
				tokenise(arg,tokens,delim);
				 for(i=0;i<8;i++)
				{
					if(tokens[i][0]!='\0')
					{
						trim(tokens[i]);
					}
					else
						break;
				}
				lscall(arg,tokens,cwd,home);
				//printf("hey\n");
			}
			else if(strcmp("pinfo",com1)==0)
			{
				char tokens[100][1024];
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
			else if(strcmp("setenv",com1)==0)
			{
				seten(arg);
			}
			else if(strcmp("unsetenv",com1)==0)
			{
				unseten(arg);
			}
			else if(strcmp("jobs",com1)==0)
			{
				jobs();
			}
			else if(strcmp("kjob",com1)==0)
			{
				kjob(arg);
			}
			else if(strcmp("fg",com1)==0)
			{
				fg(arg);
			}
			else if(strcmp("bg",com1)==0)
			{
				bg(arg);
			}
			else if(strcmp("overkill",com1)==0)
			{
				//char tem[20];
				for(int g=curi-1;g>=0;g--)
					{
						char tem[20];
						snprintf(tem,20,"%d %d",g+1,9);
						kjob(tem);
					}
			}
			else if(strcmp("history",com1)==0)
			{
				trim(arg);
				history_upd(com1,arg,home,1);
				continue;

			}
			else
			{
				syscom(com1,arg);
			}
			history_upd(com1,arg,home,0);
		
	}
	if(ex==1)
		break;
	for(i=0;i<1024;i++)
	{
		maincommand[i]='\0';
	}

	}

return 0;

}

