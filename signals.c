void ctrlC(int sig)
{
	for(int i=0;i<curi;i++)
	{
		pid_t pid = getpid();
		if(pidsave[i]==pid)
		{
			exit(0);
			return;
		}
	}
	return;
}

void ctrlZ(int sig)
{
	//printf("Hye\n");
	if(curfg==0)
		return;
	else{
	strcpy(commandcnt[curi],maincommand);

	pid_t pid = getpid();
	pidsave[curi] = curfg;
	curi++;
	printf("\033[01;33m	%s with PID %d pushed to background \033[0;31m\n",commandcnt[curi-1],pidsave[curi-1]);
	curfg = 0;
	return;
}
}
