//2012136020_김동우_LowCopy.c

//다른 헤더파일에 영향을 미치는 POSIX규격에 관련한 플래그를 정의하기에 가장 첫줄에 표기
#include<unistd.h>
//파일 상태에 대한 정보를 얻어오는 헤더파일
#include<sys/stat.h>
//이미 열려있는 파일의 특성 제어를 위하여 사용 fncl함수를 포함한 헤더파일
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
 
int main()
{

	char block[64];
	int in, out;
	int nread;
	int count = 0;
	//O_RODNLY : 읽기 전용으로 파일을 연다. 
	//about_linux.txt라는 파일을 복사한다. -> 복사할 프로그램을 내부에 고정
	in = open("about_linux.txt", O_RDONLY);
	//O_WRONLY : 쓰기 전용으로 파일을 연다
	//O_CREAT : 필요하다면 파일을 생성, mode에 주어진 권한을 적용
	//S_IRUSR : 현재 사용자에 read권한 부여
	//I_WUSRT : 현재 사용자에 write권한 부여
	//복사될 프로그램 명 : low_file.out
	out = open("low_file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	/*
	read(int filedescriptor, void *buf, size_t count)
	filedescriptor : 읽기 작업을 수행할 파일에 대한 파일 기술자
	buf : 파일로 부터 읽어 들인 내용을 저장하기 위한 공간
	count : 읽어 들일 파일의 내용 크기를 지정
	*/
	while ((nread = read(in, block, sizeof(block))) > 0) {
		/*
		write(int filedescriptor, void *buf, size_count)
		buf : 파일로 부터 쓰련느 내용을 저장하기 위한 공간
		count : 버퍼에 있는 데이터 중 실제로 파일을 저장할 데이터 크기를 지정
		*/
		write(out, block, nread);
		count++;
		//버퍼의 크기를 64byte 블록 단위로 파일을 복사
		//64byte가 되었을 때 "."을 출력
		if (count % 64 == 0)
			printf("."); 

	}

	printf("\nCopy is Finished.\n");
	exit(0);

}
