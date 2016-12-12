#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/shm.h>
#include <signal.h>

#define SM_KEY 1234


typedef struct Data{
	char name[10];
	int student_id;
	int sender_pid;
}Data;

int main(char argc,char* argv[]){
	int fd;
	int producer_pid;
	int shmid;
	Data *shared_memory;


	shmid = shmget((key_t)SM_KEY,sizeof(Data),0666);
	if(shmid == -1){
		perror("shmget failed.\n");
		exit(0);
	}

	shared_memory = shmat(shmid,NULL,0);
	if(!shared_memory){
		perror("shmat failed.\n");
		exit(0);
	}
	

	printf("consumer\n");
	printf("student id : %d , producer pid : %d\n",shared_memory->student_id, shared_memory->sender_pid);

	producer_pid = shared_memory->sender_pid;
	shared_memory->sender_pid = getpid();
	strcpy(shared_memory->name,"KIMDONGWOO");

	kill((pid_t)producer_pid,SIGALRM);


	return 1;
}
