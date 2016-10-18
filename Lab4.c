#include<stdio.h>
#include<stdlib.h>


int main(int argc, char* argv[]){
	// $HOME $PS1 $PATH $LD_LIBRARY_PATH 출력
	printf("$HOME:%s\n", getenv("HOME"));
	printf("$PS1:%s\n", getenv("PS1"));
	printf("$PATH:%s\n", getenv("PATH"));
	printf("$LD_LIBRARY_PATH:%s\n", getenv("LD_LIBRARY_PATH"));
	
	// TEST_ENV setenv()함수 사용
	printf("TEST_ENV ==> SET ENV\n");
	if(setenv("TEST_ENV","1234",1) == -1){
		printf("TEST_ENV ==> setenv() failed\n");
	}
	else{
		printf("TEST_ENV ==> setenv() successed\nvalid only at this process\n");
	}	
	printf("$TEST_ENV: %s\n", getenv("TEST_ENV"));

	return 0;
}
