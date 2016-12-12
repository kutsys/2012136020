#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int verify_parameters(char argc, char **argv){
	int i;
	char ch;
	char e=0,p=0,s=0;
	if(argc<2){
		printf("Please enter parameters.\n");
		exit(0);
	}else if(argc>3){
		printf("Too many parameters.\n");
		exit(0);
	}else if(argc ==3){
		if(argv[1][0] != '-'){
			printf("Invalid parameters.\n");
			exit(0);
		}
		while( (ch = getopt(argc-1,argv,"eps")) != -1){
			switch(ch){
				case 'e':
					e=1;
					break;
				case 'p':
					p=2;
					break;
				case 's':
					s=4;
					break;
				case '?':
					printf("Invalid parameters.\n");
					exit(0);
			}
		}	

	}
	return e|p|s;
}
