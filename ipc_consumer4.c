#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_NAME "server_pipe"

typedef struct Data{
	char name[10];
	int student_id;
	int sender_pid;
}Data;

int main(char argc,char* argv[]){
	int fd;
	Data data;

	int sockfd,len;
	struct sockaddr_un address;

	sockfd = socket(AF_UNIX,SOCK_STREAM,0);
	
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path,SOCK_NAME);
	len = sizeof(address);

	if(-1 == connect(sockfd, (struct sockaddr *)&address, len)){
		perror("client connect error.\n");
		exit(0);
	}

	read(sockfd,&data,sizeof(data));
	printf("consumer\n");
	printf("student id : %d , producer pid : %d\n",data.student_id, data.sender_pid);
	
	data.sender_pid = getpid();
	strcpy(data.name,"KIMDONGWOO");

	write(sockfd,&data,sizeof(data));

	close(sockfd);
	return 1;
}
