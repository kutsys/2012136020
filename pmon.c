#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int getPID(char *process_name){
	int pid = -1;

	char cmd_result[1024];
	FILE *fp;

	//문자열 만들기
	sprintf(cmd_result,"ps -eaf | grep -w %s | grep -v grep | awk '{print $2}'",process_name);

	//해당 문자열 실행
	fp = popen(cmd_result,"r");
	if(fp != NULL){
		//pid 얻기
		fseek(fp,0,SEEK_SET);
		fscanf(fp,"%d",&pid);

		fclose(fp);
	}


	return pid;
}
		
void check_process(){
	//pid 값 얻어오기
	int pid = getPID("ptest");
	if(pid == -1){
		printf("not existed\n");
	}else{
		printf("running\n");
	}
	//5초에 한번씩 알람
	alarm(5);
}

int main(int argc,char* argv[]){

	char command=0;
	int pid;
	//프로세스 체크 함수 알람에 등록
	signal(SIGALRM,check_process);
	alarm(5);

	while(command != 'q'){
		printf(">>");
		scanf("%c",&command);
		//버퍼 비우기
		while(getchar()!='\n');
		pid = getPID("ptest");
		switch(command){
			case 'Q':
			case 'q':
				printf("프로그램 종료\n");
				command='q';
				break;
			case 'K':
			case 'k':
				if(pid != -1){
					kill(pid,SIGKILL);
				}else{
					printf("not existed\n");
				}
				break;
			case 'S':
			case 's':
				if(pid != -1){
					printf("already running\n");
				}else{
					system("./ptest &");
				}
				break;
			case 'R':
			case 'r':
				if(pid != -1){
					kill(pid,SIGKILL);
				}else{
					printf("newly started\n");
				}
				system("./ptest &");
		}
	}
}
