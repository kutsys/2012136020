#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234


typedef struct Data{
	long mtype;
	char name[10];
	int student_id;
	int sender_pid;
}Data;

int main(char argc,char* argv[]){
	int fd;
	key_t msg_key;
	Data msg_buf;


	msg_key = msgget((key_t)MSG_KEY,0666|IPC_CREAT);
	if(msg_key == -1){
		perror("msgget failed.\n");
		exit(0);
	}

	if(msgrcv(msg_key,&msg_buf,sizeof(Data),1,0)==-1){
		perror("msgrcv error.\n");
		exit(0);
	}


	printf("consumer\n");
	printf("student id : %d , producer pid : %d\n",msg_buf.student_id, msg_buf.sender_pid);
	
	msg_buf.mtype=2;
	msg_buf.sender_pid = getpid();
	strcpy(msg_buf.name,"KIMDONGWOO");

	if(msgsnd(msg_key,&msg_buf,sizeof(Data),0) == -1){
		perror("msgsnd error.\n");
		exit(0);
	}

	return 1;
}
