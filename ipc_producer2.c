#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/stat.h>

#define SM_KEY 1234

typedef struct Data{
	char name[10];
	int student_id;
	int sender_pid;
}Data;

void myalarm(){

}

int main(char argc,char *argv[]){
	char start[10];
	int res, fd;
	int shmid;
	pid_t fork_pid;
	
	Data *shared_memory;

	sigset_t sig_set;
	int sig_no;
	sigemptyset(&sig_set);
	sigaddset(&sig_set,SIGALRM);

	signal(SIGALRM,myalarm);
	while(strcmp("start",start)){
		memset(start,0,10);
		printf("start typing start. : ");
		scanf("%s",start);
	}


	fork_pid = fork();
	switch(fork_pid){
		case -1:
			printf("fork_error.\n");
			exit(0);
			break;
		case 0:
			execl("./ipc_consumer2","ipc_consumer2",NULL);
	}
	
	shmid = shmget((key_t)SM_KEY,sizeof(Data),0666|IPC_CREAT);
	if(shmid == -1){
		perror("shmget failed\n");
		exit(0);
	}
	//shmat의 매핑 주소가null 이면 시스템에서 적당한 공간을 자동 할당
	shared_memory = shmat(shmid,NULL, 0);
	shared_memory->student_id = 2012136020;
	shared_memory->sender_pid = getpid();

	sigwait(&sig_set,&sig_no);

	printf("producer\n");
	printf("producer pid : %d, consumer_pid : %d\n",getpid(), shared_memory->sender_pid);
	printf("name : %s , student id : %d\n",shared_memory->name, shared_memory->student_id);


	return 1;
}
