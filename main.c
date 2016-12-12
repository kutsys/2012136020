#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "elfreader.h"
#include "util.h"


#define BUF_SIZE 100


int main(char argc,char *argv[]){
	char opt = verify_parameters(argc,argv);
	char filename[BUF_SIZE]={0};
	int m_bit;
	int fd;

	Hdr32 hdr32;
	Hdr64 hdr64;

	if(argc == 2){
		strcpy(filename,argv[1]);
	}else{
		strcpy(filename,argv[2]);
	}
	m_bit = is_elf(filename);
	fd = open(filename,O_RDONLY);

	switch(m_bit){
		case 32:
			read_headers32(fd, &hdr32);
			break;
		case 64:
			read_headers64(fd, &hdr64);
			break;
	}

	switch(opt){
		case 0:
		case OPT_E:
			print_elf_header64(hdr64.ehdr);
			break;
		case OPT_P:
			print_pro_header64(hdr64.ehdr, hdr64.phdrs);
			break;
		case OPT_S:
			print_sec_header64(fd, hdr64.ehdr, hdr64.shdrs);
			break;
		case OPT_EP:
			print_elf_header64(hdr64.ehdr);
			print_pro_header64(hdr64.ehdr, hdr64.phdrs);
			break;
		case OPT_ES:
			print_elf_header64(hdr64.ehdr);
			print_sec_header64(fd, hdr64.ehdr, hdr64.shdrs);
			break;
		case OPT_PS:
			print_pro_header64(hdr64.ehdr, hdr64.phdrs);
			print_sec_header64(fd, hdr64.ehdr, hdr64.shdrs);
			break;

		case OPT_EPS:
			print_elf_header64(hdr64.ehdr);
			print_sec_header64(fd, hdr64.ehdr, hdr64.shdrs);
			print_pro_header64(hdr64.ehdr, hdr64.phdrs);
			break;

	}

	

	//print_elf_header64(hdr64.ehdr);
	//print_sec_header64(fd, hdr64.ehdr, hdr64.shdrs);
	//print_pro_header64(hdr64.ehdr, hdr64.phdrs);
	switch(m_bit){
		case 32:
			free(hdr32.shdrs);
			free(hdr32.phdrs);
			break;
		case 64:
			free(hdr64.shdrs);
			free(hdr64.phdrs);
			break;
	}
	close(fd);
	return 1;
}
