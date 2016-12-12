#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


typedef struct Data{
	char name[10];
	int student_id;
	int sender_pid;
}Data;

#define SOCK_NAME "server_pipe"

int main(char argc,char *argv[]){
	char start[10];
	int res, fd;
	pid_t fork_pid;
	Data data;

	int server_sockfd,client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address,client_address;


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
			execl("./ipc_consumer4","ipc_consumer4",NULL);
	}
	
	unlink(SOCK_NAME);
	server_sockfd = socket(AF_UNIX,SOCK_STREAM,0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path,SOCK_NAME);
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

	listen(server_sockfd,1);

	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd,
							(struct sockaddr *)&client_address, &client_len);

	data.student_id = 2010136017;
	data.sender_pid = getpid();

	write(client_sockfd,&data,sizeof(data));
	read(client_sockfd,&data,sizeof(data));
	close(client_sockfd);

	printf("producer\n");
	printf("producer pid : %d, consumer_pid : %d\n",getpid(), data.sender_pid);
	printf("name : %s , student id : %d\n",data.name, data.student_id);


	return 1;
}
