#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

 

void printdir(char *dir, int depth)
{

	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

 	// dir에 저장된 이름의 디렉토리를 열고 그에 대한 스트림을 생성
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}
	// 현재 작업 디렉토리를 dir로 변경
	chdir(dir);

	while ((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			
			if (strcmp(".", entry->d_name) == 0 ||
				strcmp("..", entry->d_name) == 0) continue;
			//하위 디렉토리를 탐색하기 위해 재귀호출을 한다.
			if (strncmp(".", entry->d_name, 1) == 0) continue;
			printf("%*s%s/\n", depth, "", entry->d_name);
			//하위 디렉토리 출력시 줄 정리 위해 depth+4를 전달
			printdir(entry->d_name, depth + 4);
		}
		else {
			//"."으 시작하는 히든파일은 넘어간다.
			if(strncmp (".",entry->d_name,1) == 0) continue;
			printf("%*s%s\n", depth, "", entry->d_name);
		}
	}
	//printdir 함수로 진입 전에 작업하던 디렉토리로 이동
	chdir("..");
	
	//디렉토리 스트림을 닫고 그에 연관된 자원들을 해제한다.
	//성공 시 0, 오류 발생 시 -1을 반환한다. 
	closedir(dp);

}
int main()
{
	printf("Directory scan of /home:\n");
	printdir("/home", 0);
	printf("done.\n");
	exit(0);
}

