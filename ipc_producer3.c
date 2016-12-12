#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#define MSG_KEY 1234

typedef struct Data{
	long mtype;
	char name[10];
	int student_id;
	int sender_pid;
}Data;


int main(char argc,char *argv[]){
	char start[10];
	int res, fd;
	pid_t fork_pid;
	key_t msg_key;
	
	Data msg_buf;

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
			execl("./ipc_consumer3","ipc_consumer3",NULL);
	}
	
	msg_key = msgget((key_t)MSG_KEY,0666|IPC_CREAT);
	if(msg_key == -1){
		perror("msgget error. \n");
		exit(0);
	}
	msg_buf.mtype=1;
	msg_buf.student_id = 2010136017;
	msg_buf.sender_pid = getpid();

	if(msgsnd(msg_key,&msg_buf,sizeof(Data),0) == -1){
		perror("msgsnd error.\n");
		exit(0);
	}

	if(msgrcv(msg_key,&msg_buf,sizeof(Data),2,0) == -1){
		perror("msgrcv error.\n");
		exit(0);
	}

	printf("producer\n");
	printf("producer pid : %d, consumer_pid : %d\n",getpid(), msg_buf.sender_pid);
	printf("name : %s , student id : %d\n",msg_buf.name, msg_buf.student_id);


	return 1;
}
