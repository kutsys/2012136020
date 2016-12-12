#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 100
#define N_PIPE_NAME "./fifo"


typedef struct Data{
	char name[10];
	int student_id;
	int sender_pid;
}Data;

int main(char argc,char *argv[]){
	char start[10];
	int res, fd;
	Data data;
	pid_t fork_pid;
	
	while(strcmp("start",start)){
		memset(start,0,10);
		printf("start typing start. : ");
		scanf("%s",start);
	}

	if(access(N_PIPE_NAME,F_OK)==-1){
		res = mkfifo(N_PIPE_NAME,0777);
		if(res != 0){
			exit(EXIT_FAILURE);
		}
	}


	fork_pid = fork();
	switch(fork_pid){
		case -1:
			printf("fork_error.\n");
			exit(0);
			break;
		case 0:
			execl("./ipc_consumer","ipc_consumer",NULL);
	}
	

	data.student_id=2010136017;
	data.sender_pid = getpid();

	fd = open(N_PIPE_NAME,O_WRONLY);
	write(fd, &data,sizeof(data));
	close(fd);

	fd = open(N_PIPE_NAME,O_RDONLY);
	read(fd,&data,sizeof(data));
	close(fd);

	printf("producer\n");
	printf("producer pid : %d, consumer_pid : %d\n",getpid(), data.sender_pid);
	printf("name : %s , student id : %d\n",data.name, data.student_id);

	unlink(N_PIPE_NAME);

	return 1;
}
