int tokenise(char *inp,char tokens[100][1024],char *delim);
void kjob(char *inp);

void bg(char *inp)
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
		int x = pidsave[num-1];
		kill(x,SIGCONT);		
	} 

}
