int tokenise(char *inp,char tokens[100][1024],char *delim);

void kjob(char *inp)
{

	char delim[] = " \t\r\n\v\f";
    char tokens[100][1024];
    int a = tokenise(inp,tokens,delim);

    if(a<2 || a>2)
    {
    	printf("\033[1;31mIncorrect number of arguments.\033[0m :(\n");
    }
    else
    {
    	int num = atoi(tokens[0]);
    	int signaltype = atoi(tokens[1]);
    	if(num<0 || num>curi)
    	{
    		printf("\033[1;31mInvalid Job number.\033[0m :(\n");
    	}
    	else
    	{
    		kill(pidsave[num-1],signaltype);
    	}

    }
}