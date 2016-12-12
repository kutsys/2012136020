#ifndef _ELFREADER_H_
#define _ELFREADER_H_
#include <elf.h>

#define OPT_E 1
#define OPT_P 2
#define OPT_S 4
#define OPT_EP 3
#define OPT_ES 5
#define OPT_PS 6
#define OPT_EPS 7

typedef struct Hdr32{
	Elf32_Ehdr ehdr;
	Elf32_Shdr *shdrs;
	Elf32_Phdr *phdrs;
}Hdr32;

typedef struct Hdr64{
	Elf64_Ehdr ehdr;
	Elf64_Shdr *shdrs;
	Elf64_Phdr *phdrs;
}Hdr64;

int is_elf(char *filename);

void read_headers32(int fd,Hdr32 *hdrs);
void read_headers64(int fd,Hdr64 *hdrs);

void read_elf_header32(int fd, Elf32_Ehdr *ehdr);
void read_elf_header64(int fd, Elf64_Ehdr *ehdr);

void read_sec_header32(int fd, Elf32_Ehdr ehdr, Elf32_Shdr *shdrs);
void read_sec_header64(int fd, Elf64_Ehdr ehdr, Elf64_Shdr *shdrs);

char* read_string_table32(int fd, Elf32_Shdr shdr);
char* read_string_table64(int fd, Elf64_Shdr shdr);

void read_program_header32(int fd, Elf32_Ehdr ehdr, Elf32_Phdr *phdrs);
void read_program_header64(int fd, Elf64_Ehdr ehdr, Elf64_Phdr *phdrs);

void print_elf_header32(Elf32_Ehdr ehdr);
void print_elf_header64(Elf64_Ehdr ehdr);

void print_sec_header32(int fd, Elf32_Ehdr ehdr, Elf32_Shdr shdrs[]);
void print_sec_header64(int fd, Elf64_Ehdr ehdr, Elf64_Shdr shdrs[]);

void print_pro_header64(Elf64_Ehdr ehdr, Elf64_Phdr phdrs[]);

#endif
