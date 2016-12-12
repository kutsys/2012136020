#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_SIZE 100
#define N_PIPE_NAME "./fifo"


typedef struct Data{
	char name[10];
	int student_id;
	int sender_pid;
}Data;

int main(char argc,char* argv[]){
	int fd;
	int mypid =getpid();
	Data data;

	if(access(N_PIPE_NAME,F_OK) == -1){
		if(mkfifo(N_PIPE_NAME,0777) != 0){
			exit(0);
		}
	}
	fd = open(N_PIPE_NAME,O_RDONLY);

	read(fd,&data,sizeof(data));
	close(fd);

	printf("consumer\n");
	printf("student id : %d , producer pid : %d\n",data.student_id, data.sender_pid);

	fd = open(N_PIPE_NAME,O_WRONLY);
	
	strcpy(data.name,"KIMDONGWOO");
	data.sender_pid = getpid();

	write(fd,&data,sizeof(data));
	close(fd);

	return 1;
}
