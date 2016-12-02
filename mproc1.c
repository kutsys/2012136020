#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>

//defines
#define FUNC_COUNT 20
#define NUM_OF_PROCESS 10

int killed = 0;


void release_sub(int sig)
{
	printf("I AM CALLED!\n");
	if(sig == SIGALRM){
		int stat_val;
		killed++;
		printf("Killed : %d\n" , killed);
		wait(&stat_val);
	}
}

int main(void)
{
	pid_t funct_pid;
	char buffer[1024];
	char send1[128];
	char send2[128];
	int i;
	int send_pid = getpid();
	(void)signal(SIGALRM,release_sub);

	for(i = 0; i< 10 ; i++)
	{
		funct_pid = fork();
		switch(funct_pid)
		{
			case -1:
				perror("fork failed"); exit(1);
			case 0: // child
				sprintf(send1,"%d",send_pid);
				sprintf(send2,"%d",FUNC_COUNT);
				exit(1);
				break;
			default: // parent
				break;

		}	
	}

	while(1)
	{
		if(killed == 10)
		{
			printf("Process Finished!\n");
			break;
		}
		pause();
	}


	
	return 0;
}
