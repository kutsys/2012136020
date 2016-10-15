//2012136020_김동우_HighCopy.c
#include<stdio.h>
#include<stdlib.h>


int main()
{

	char block[64];
	FILE *in, *out;
	int nread;
	int count = 0;
 
	//FILE *fopen(const char *filename, const char *mode)
	//filename : 매개변수의 이름을 가진 파일을 열고 스트림에 연결한다.
	//mode의 경우 문자열로 나타낼 수 있다.
	//복사될 프로그램 내부에 고정 : about_linux.txt
	in = fopen("about_linux.txt", "rb");
	//복사되어 저장될 프로그램 명 : high_filie.out
	out = fopen("high_file.out", "wb");



	while (!feof(in)) {
		//fread : 파일 스트림으로 부터 데이터를 읽기 위하여 사용
		//데이터는 스트림으로 부터 ptr로 주어진 제이터 버퍼로 저장
		nread = fread(block, sizeof(block), 64, in);
		// 지정된 데이터 버퍼에 있는 데이터 레코드를 출력 스트림으로 사용
		fwrite(block, sizeof(block), nread, out);
		count++;
		//lowcopy때와 마찬가지로 버퍼를 64byte로 설정한다.
		//asterlisk(*)를 출력한다.
		if (count % 64 == 0)printf("*");

	}
	printf("\nCopy is Finished\n");
	//stdio라이브러리에서는 데이터를 버퍼링 하기 때문에 파일을 닫아 준다.
	fclose(in);
	fclose(out);
	exit(0);
}
