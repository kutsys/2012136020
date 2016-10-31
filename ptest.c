#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>


void what_time(){
	struct tm *tm_ptr;
	time_t the_time;

	(void)time(&the_time);
	tm_ptr = localtime(&the_time);

	printf("%d/%d/%d %d:%d:%d\n",
			tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday,
			tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec);
}

int main(int argc,char* argv[]){
	//알람 시그널에 시간 출력 함수 등록
	signal(SIGALRM,what_time);

	what_time();
	while(1){
		alarm(2);
		pause();
	}


	return 0;
}
