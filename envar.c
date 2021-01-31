int tokenise(char *inp,char tokens[100][1024],char *delim);
void trim(char *inp);

void unseten(char *inp)
{
	char tokens[100][1024];
	char delim[] = " \t\r\n\v\f";
	int a  = tokenise(inp,tokens,delim);
	if(a>1 || a==0)
	{
		printf("\033[1;31mIncorrect number of arguments\033[0m :(\n");
	}
	else
	{
		int k = unsetenv(tokens[0]);
		if(k<0)
		{
			perror("\033[1;31mError\033[0m");
		}
	}

}


void seten(char *inp)
{
	char tokens[100][1024];
	char delim[] = " \t\r\n\v\f";
	int a  = tokenise(inp,tokens,delim);

	if(a==0 || a>2)
	{
		printf("\033[1;31mIncorrect number of arguments\033[0m :(\n");
	}
	else
	{
		if(a==1)
		{
			int k = setenv(tokens[0],"\0",2);
			if(k<0)
			{
			perror("\033[1;31mError\033[0m");
			}
		}
		else if(a==2)
		{
			//printf("%s\n",tokens[0],tokens[1]);
			int k = setenv(tokens[0],tokens[1],2);
			if(k<0)
			{	
			perror("\033[1;31mError\033[0m");
			}
		}
	}
}