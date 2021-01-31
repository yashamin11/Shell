int tokenise(char *inp,char tokens[100][1024],char *delim);

void jobs()
{
	int i;
	for(i=0;i<curi;i++)
	{
		char temp[1024];
		sprintf(temp,"/proc/%d/status", pidsave[i]);
		FILE *fp;
	 	fp = fopen(temp,"r");
	 	if(fp<=0)
		{
			perror("\033[1;31mError\033[0m :(");
		}
		else
		{
			//flclose(fp);

			char info[1024];
			//int i = 0;
			int k=0;
			while(fgets(info,1024,fp)!=NULL)
			{
				k++;
				if(k==3)
				{
					break;
				}

			}
			fclose(fp);
            //char *temp = status_info;
            char delim[] = " \t\r\n\v\f";
            char tokens[100][1024];
            int a = tokenise(info,tokens,delim);
           // printf("%s\n",tokens[1]);
            if(tokens[1][0]!='T')
            {
            	printf("\033[1;36m[%d] Running %s [%d]\033[0m\n",i+1,commandcnt[i],pidsave[i]);
            }
            else
            {
            	printf("\033[1;36m[%d] Stopped %s [%d]\033[0m\n",i+1,commandcnt[i],pidsave[i]);
            }
		}
	}

}