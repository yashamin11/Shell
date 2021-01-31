int cd (char *inp, char *cwd,char *home)
{

	for(int i=0;i<1024;i++)
		cwd[i] = '\0';

	if(inp[0]=='-')
	{
		if(changeflag)
		{
			if(strstr(lastdir,home)!=NULL)
			{
				char tempi[1024],teemp1[1024];
				for(int i=0;i<1024;i++)
					{tempi[i]='\0';teemp1[i]='\0';}
				//getcwd(cwd,1024);
				strcpy(tempi,lastdir);
				// printf("%s\n",home);
				// printf("%s\n",lastdir);
				// printf("%s   %s\n",tempi,teemp1);
		
				int j = strlen(home);
				j++;int i=0;
				while(tempi[j]!='\0')
					{teemp1[i] = tempi[j];
				i++;j++;}
				teemp1[i]='\0';
				if(strcmp(lastdir,home)==0)
					{
						printf("~\n");
						cd("~",cwd,home);
					}
				else
				{

					printf("~/%s\n",teemp1);
					char yeah[] = "~/";
					strcat(yeah,teemp1);
					//printf("%s\n",yeah);
					cd(yeah,cwd,home);
				}
				
			}
			else
			{
				printf("%s\n",lastdir);
				cd(lastdir,cwd,home);

			}

		}
		else
			return 0;
	}
	else if(inp[0]!='~')
	{
		//strcpy(lastdir,inp);
	
		char backupp[1024];
		strcpy(backupp,lastdir);
		getcwd(lastdir,1024);

		//strcpy(backupp,lastdir);

		int  k =chdir(inp);

		if(k<0)
		{
			strcpy(lastdir,backupp);
			printf("\033[1;31mNo such Directory \033[0m:(\n");
			getcwd(cwd,1024);
			return 1;

		}

		getcwd(cwd,1024);
		
	}
	
	else
	{
		char temp[1024];
		strcpy(temp,inp);
		memmove(temp, temp+1, sizeof(temp));
		strcpy(cwd,home);
		strcat(cwd,temp);
		//strcpy(lastdir,cwd);
		char backupp[1024];
		strcpy(backupp,lastdir);
		getcwd(lastdir,1024);
		
		int k = chdir(cwd);
		if(k==-1)
		{
			strcpy(lastdir,backupp);
			printf("No such Directory :(\n");
			return 1;
		}
		
	}
	return 0;

}