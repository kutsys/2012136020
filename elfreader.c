
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "elfreader.h"

int is_elf(char *filename){
	char checker[5];
	int fd;
	int i;
	if((fd = open(filename,O_RDONLY)) == -1){
		printf("Please check the file name.\n");	
		exit(0);
	}
	read(fd,checker,5);
	close(fd);
	if(checker[0] != 127 ||
		checker[1] != 'E' ||
		checker[2] != 'L' ||
		checker[3] != 'F'){
		printf("It is not an elf file.\n");
		exit(1);
	}
	return checker[4] == 1 ? 32 : 64;
}

void read_headers32(int fd,Hdr32 *hdrs){
	read_elf_header32(fd,&(hdrs->ehdr));
	hdrs->shdrs = (Elf32_Shdr *)malloc(hdrs->ehdr.e_shentsize * hdrs->ehdr.e_shnum);
	read_sec_header32(fd,hdrs->ehdr,hdrs->shdrs);
	hdrs->phdrs = (Elf32_Phdr *)malloc(hdrs->ehdr.e_phentsize * hdrs->ehdr.e_phnum);
	read_program_header32(fd,hdrs->ehdr,hdrs->phdrs);

}
void read_headers64(int fd,Hdr64 *hdrs){
	read_elf_header64(fd,&(hdrs->ehdr));
	hdrs->shdrs = (Elf64_Shdr *)malloc(hdrs->ehdr.e_shentsize * hdrs->ehdr.e_shnum);
	read_sec_header64(fd,hdrs->ehdr,hdrs->shdrs);
	hdrs->phdrs = (Elf64_Phdr *)malloc(hdrs->ehdr.e_phentsize * hdrs->ehdr.e_phnum);
	read_program_header64(fd,hdrs->ehdr,hdrs->phdrs);
}

void read_elf_header32(int fd, Elf32_Ehdr *ehdr){
	lseek(fd, (off_t)0, SEEK_SET);
	read(fd, ehdr, sizeof(Elf32_Ehdr));
}

void read_elf_header64(int fd, Elf64_Ehdr *ehdr){
	lseek(fd, (off_t)0, SEEK_SET);
	read(fd, ehdr, sizeof(Elf64_Ehdr));
}

void read_sec_header32(int fd, Elf32_Ehdr ehdr,  Elf32_Shdr *shdrs){
	int i;
	
	lseek(fd, (off_t)ehdr.e_shoff, SEEK_SET);
	for(i =0; i<ehdr.e_shnum;i++){
		read(fd,&shdrs[i],ehdr.e_shentsize);
	}
}
void read_sec_header64(int fd, Elf64_Ehdr ehdr,  Elf64_Shdr *shdrs){
	int i;
	
	lseek(fd, (off_t)ehdr.e_shoff, SEEK_SET);
	for(i =0; i<ehdr.e_shnum;i++){
		read(fd,&shdrs[i],ehdr.e_shentsize);
	}
}

char *read_string_table32(int fd, Elf32_Shdr shdr){
	char* buf = (char*)malloc(shdr.sh_size);
	
	lseek(fd,(off_t)shdr.sh_offset, SEEK_SET);
	read(fd,buf, shdr.sh_size);

	return buf;
}

char *read_string_table64(int fd, Elf64_Shdr shdr){
	char* buf = (char*)malloc(shdr.sh_size);
	
	lseek(fd,(off_t)shdr.sh_offset, SEEK_SET);
	read(fd,buf, shdr.sh_size);

	return buf;
}

void read_program_header32(int fd, Elf32_Ehdr ehdr, Elf32_Phdr *phdrs){
	int i;

	lseek(fd, (off_t)ehdr.e_phoff, SEEK_SET);
	for(i = 0;i<ehdr.e_phnum;i++){
		read(fd,&phdrs[i],ehdr.e_phentsize);
	}

}
void read_program_header64(int fd, Elf64_Ehdr ehdr, Elf64_Phdr *phdrs){
	int i;

	lseek(fd, (off_t)ehdr.e_phoff, SEEK_SET);
	for(i = 0;i<ehdr.e_phnum;i++){
		read(fd,&phdrs[i],ehdr.e_phentsize);
	}
}

void print_elf_header64(Elf64_Ehdr ehdr){
	int i;

	printf("*** ELF HEADERS ***\n");
	printf("Magic :");
	for(i=0; i<sizeof(ehdr.e_ident);i++){
		printf("%02X ",ehdr.e_ident[i]);
	}
	printf("\n");
	
	printf("Class : ");
	switch(ehdr.e_ident[EI_CLASS]){
	case ELFCLASSNONE:
		printf("Invalid class"); break;
	case ELFCLASS32:
		printf("32-bit objects"); break;
	case ELFCLASS64:
		printf("64-bit objects"); break;
	}
	printf("\n");

	printf("Data : ");
	switch(ehdr.e_ident[EI_DATA]){
		case ELFDATANONE:
			printf("Invalid data encoding"); break;
		case ELFDATA2LSB:
			printf("2's complement, little endian"); break;
		case ELFDATA2MSB:
			printf("2's complement, big endian"); break;
	}
	printf("\n");

	printf("Version : ");
	switch(ehdr.e_ident[EI_VERSION]){
		case EV_NONE:
			printf("Invalid version"); break;
		case EV_CURRENT:
			printf("Current version"); break;
	}
	printf("\n");

	printf("OS/ABI : ");
	switch(ehdr.e_ident[EI_OSABI]){
		case ELFOSABI_SYSV:
			printf("UNIX System V ABI"); break;
		case ELFOSABI_HPUX:
			printf("HP-UX"); break;
		case ELFOSABI_NETBSD:
			printf("NetBSD"); break;
		case ELFOSABI_GNU:
			printf("Object uses GNU ELF extensions"); break;
		case ELFOSABI_SOLARIS:
			printf("Sun Solaris"); break;
		case ELFOSABI_AIX:
			printf("IBM AIX"); break;
		case ELFOSABI_IRIX:
			printf("SGI Irix"); break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD"); break;
		case ELFOSABI_TRU64:
			printf("Compaq TRU64 UNIX"); break;
		case ELFOSABI_MODESTO:
			printf("Novell Modesto"); break;
		case ELFOSABI_OPENBSD:
			printf("OpenBSD"); break;
		case 13:
			printf("OpenVMS"); break;
		case ELFOSABI_ARM_AEABI:
			printf("ARM EABI"); break;
		case ELFOSABI_ARM:
			printf("ARM"); break;
		case ELFOSABI_STANDALONE:
			printf("Standalone (embedded) application"); break;

	}
	printf("\n");

	printf("ABI version : %d \n",ehdr.e_ident[EI_ABIVERSION]);

	/* EL+PAD(0x09) Byte index of padding bytes. */

	printf("Type : ");
	switch(ehdr.e_type){
		case ET_NONE:
			printf("No file type"); break;
		case ET_REL:
			printf("Relocatable file"); break;
		case ET_EXEC:
			printf("Executable file"); break;
		case ET_DYN:
			printf("Shared object file"); break;
		case ET_CORE:
			printf("Core file");

	}
	printf("\n");
	
	printf("Machine : ");
	switch(ehdr.e_machine){
		case EM_NONE:
			printf("No machine"); break;
		case EM_M32:
			printf("AT&T WE 32100"); break;
		case EM_SPARC:
			printf("SUN SPARC"); break;
		case EM_386:
			printf("Intel 80386"); break;
		case EM_68K:
			printf("Motorola m68k family"); break;
		case EM_88K:
			printf("Motorola m88k family"); break;
		case EM_860:
			printf("Intel 80860"); break;
		case EM_MIPS:
			printf("MIPS R3000 big-endian"); break;
		case EM_S370:
			printf("IBM System/370"); break;
		case EM_MIPS_RS3_LE:
			printf("MIPS R3000 little-endian"); break;
		case EM_PARISC:
			printf("HPPA"); break;
		case EM_VPP500:
			printf("Fujitsu VPP500"); break;
		case EM_SPARC32PLUS:
			printf("Sun's \"v8plus\""); break;
		case EM_960:
			printf("Intel 80960"); break;
		case EM_PPC:
			printf("PowerPC"); break;
		case EM_PPC64:
			printf("PowerPC 64-bit"); break;
		case EM_S390:
			printf("IBM S390"); break;
		case EM_V800:
			printf("NEC V800 series"); break;
		case EM_FR20:
			printf("Fujitsu FR20"); break;
		case EM_RH32:
			printf("TRW RH-32"); break;
		case EM_RCE:
			printf("Motorola RCE"); break;
		case EM_ARM:
			printf("ARM"); break;
		case EM_FAKE_ALPHA:
			printf("Digital Alpha"); break;
		case EM_SH:
			printf("Hitachi SH"); break;
		case EM_SPARCV9:
			printf("SPARC v9 64-bit"); break;
		case EM_TRICORE:
			printf("Siemens Tricore"); break;
		case EM_ARC:
			printf("Argonaut RISC Core"); break;
		case EM_H8_300:
			printf("Hitachi H8/300"); break;
		case EM_H8_300H:
			printf("Hitachi H8/300H"); break;
		case EM_H8S:
			printf("Hitachi H8S"); break;
		case EM_H8_500:
			printf("Hitachi H8/500"); break;
		case EM_IA_64:
			printf("Intel Merced"); break;
		case EM_MIPS_X:
			printf("Stanford MIPS-X"); break;
		case EM_COLDFIRE:
			printf("Motorola Coldfire"); break;
		case EM_68HC12:
			printf("Motorola M68HC12"); break;
		case EM_MMA:
			printf("Fujitsu MMA Multimedia Accelerator"); break;
		case EM_PCP:
			printf("Siemens PCP"); break;
		case EM_NCPU:
			printf("Sony nCPU embeeded RISC"); break;
		case EM_NDR1:
			printf("Denso NDR1 microprocessor"); break;
		case EM_STARCORE:
			printf("Motorola Start Core processor"); break;
		case EM_ME16:
			printf("Toyota ME16 processor"); break;
		case EM_ST100:
			printf("STMicroelectronic ST100 processor"); break;
		case EM_TINYJ:
			printf("Advanced Logic Corp. Tinyj emb.fam"); break;
		case EM_X86_64:
			printf("AMD x86-64 architecture"); break;
		case EM_PDSP:
			printf("Sony DSP Processor"); break;
		case EM_FX66:
			printf("Siemens FX66 microcontroller"); break;
		case EM_ST9PLUS:
			printf("STMicroelectronics ST9+ 8/16 mc"); break;
		case EM_ST7:
			printf("STmicroelectronics ST7 8 bit mc"); break;
		case EM_68HC16:
			printf("Motorola MC68HC16 microcontroller"); break;
		case EM_68HC11:
			printf("Motorola MC68HC11 microcontroller"); break;
		case EM_68HC08:
			printf("Motorola MC68HC08 microcontroller"); break;
		case EM_68HC05:
			printf("Motorola MC68HC05 microcontroller"); break;
		case EM_SVX:
			printf("Silicon Graphics SVx"); break;
		case EM_ST19:
			printf("STMicroelectronics ST19 8 bit mc"); break;
		case EM_VAX:
			printf("Digital VAX"); break;
		case EM_CRIS:
			printf("Axis Communications 32-bit embedded processor"); break;
		case EM_JAVELIN:
			printf("Infineon Technologies 32-bit embedded processor"); break;
		case EM_FIREPATH:
			printf("Element 14 64-bit DSP Processor"); break;
		case EM_ZSP:
			printf("LSI Logic 16-bit DSP Processor"); break;
		case EM_MMIX:
			printf("Donald Knuth's educational 64-bit processor"); break;
		case EM_HUANY:
			printf("Harvard University machine-independent object files"); break;
		case EM_PRISM:
			printf("SiTera Prism"); break;
		case EM_AVR:
			printf("Atmel AVR 8-bit microcontroller"); break;
		case EM_FR30:
			printf("Fujitsu FR30"); break;
		case EM_D10V:
			printf("Mitsubishi D10V"); break;
		case EM_D30V:
			printf("Mitsubishi D30V"); break;
		case EM_V850:
			printf("NEC v850"); break;
		case EM_M32R:
			printf("Mitsubishi M32R"); break;
		case EM_MN10300:
			printf("Matsushita MN10300"); break;
		case EM_MN10200:
			printf("Matsushita MN10200"); break;
		case EM_PJ:
			printf("picoJava"); break;
		case EM_OPENRISC:
			printf("OpenRISC 32-bit embedded processor"); break;
		case EM_ARC_A5:
			printf("ARC Cores Tangent-A5"); break;
		case EM_XTENSA:
			printf("Tensilica Xtensa Architecture"); break;
		case EM_ALTERA_NIOS2:
			printf("Altera Nios II"); break;
		case EM_AARCH64:
			printf("ARM AARCH64"); break;
		case EM_TILEPRO:
			printf("Tilera TILEPro"); break;
		case EM_MICROBLAZE:
			printf("Xilinx MicroBlaze"); break;
		case EM_TILEGX:
			printf("Tilera TILE-Gx"); break;
	}
	printf("\n");

	printf("Version : 0x%02X\n",ehdr.e_version);

	/* 64 bits are 8 bytes 32 bits are 4 bytes. */
	printf("Entry point address : 0x%06jX\n",ehdr.e_entry);

	/* 64 bits are 8 bytes 32 bits are 4 bytes. */
	printf("Start of program headers : %jd\n",ehdr.e_phoff);

	/* 64 bits are 8 bytes 32 bits are 4 bytes. */
	printf("Start of section headers : %jd\n",ehdr.e_shoff);

	printf("Flags : 0x%02X\n",ehdr.e_flags);
	
	printf("Size of this header : %d (bytes)\n",ehdr.e_ehsize);

	printf("Size of program headers : %d (bytes)\n",ehdr.e_phentsize);

	printf("Number of program headers : %d \n",ehdr.e_phnum);

	printf("Size of section headers : %d (bytes)\n",ehdr.e_shentsize);
	
	printf("Number of section headers : %d \n",ehdr.e_shnum);

	printf("Section header string table index : %d\n",ehdr.e_shstrndx);


}


void print_sec_header64(int fd, Elf64_Ehdr ehdr, Elf64_Shdr shdrs[]){
	int i;
	char *string_table;
	int flag;
	int remain_space = 0;
	string_table = read_string_table64(fd, shdrs[ehdr.e_shstrndx]);

	printf("\n*** SECTION HEADERS ***\n");
	printf("[Num] Name              Type               Address           Offset  \n"
			"      Size              EntSize            Flags  Link  Info  Align\n");
	for(i=0;i<ehdr.e_shnum;i++){
		printf("[%-3d] ",i);
		printf("%-16s ",(string_table+shdrs[i].sh_name));
		printf("0x%016X ",shdrs[i].sh_type);
		printf("0x%016jX ",shdrs[i].sh_addr);
		printf("0x%08jX ",shdrs[i].sh_offset);
		
		printf("\n      ");

		printf("0x%016jX ",shdrs[i].sh_size);
		printf("0x%016jX ",shdrs[i].sh_entsize);
	
		remain_space = 7;
		flag = (int)shdrs[i].sh_flags;

		printf("%7jX ",shdrs[i].sh_flags);
		printf("%-6X ",shdrs[i].sh_link);
		printf("%-6X ",shdrs[i].sh_info);
		printf("%-6jX ",shdrs[i].sh_addralign);

		printf("\n");

	}

}

void print_pro_header64(Elf64_Ehdr ehdr, Elf64_Phdr *phdrs){
	int i;
	printf("\n*** PROGRAM HEADERS ***\n");
	printf("Type            Offset             VirtAddr           PhysAddr\n"
			"                FileSize           MemSize            Flags   Align\n");
	for(i=0;i<ehdr.e_phnum;i++){
		switch(phdrs[i].p_type){
			case PT_LOAD:
				printf("LOAD            ");
				break;
			case PT_DYNAMIC:
				printf("DYNAMIC         ");
				break;
			case PT_INTERP:
				printf("INTERP          ");
				break;
			case PT_NOTE:
				printf("NOTE            ");
				break;
			case PT_SHLIB:
				printf("SHLIB           ");
				break;
			case PT_PHDR:
				printf("PHDR            ");
				break;
			case PT_TLS:
				printf("TLS             ");
				break;
			case PT_LOOS:
				printf("LOOS            ");
				break;
			case PT_GNU_EH_FRAME:
				printf("GNU_EH_FRAME    ");
				break;
			case PT_GNU_STACK:
				printf("GNU_STACK       ");
				break;
			case PT_GNU_RELRO:
				printf("GNU_RELRO       ");
				break;
		//	case PT_LOSUNW:
		//		printf("LOSUNW          ");
		//		break;
			case PT_SUNWBSS:
				printf("SUNWBSS         ");
				break;
			case PT_SUNWSTACK:
				printf("SUNWSTACK       ");
				break;
			case PT_HISUNW:
				printf("HISUNW          ");
				break;
		//	case PT_HIOS:
		//		printf("HIOS            ");
	//			break;
			case PT_LOPROC:
				printf("PT_LOPROC       ");
				break;
		//	case PT_HIPROC:
		//		printf("PT_HIPROC       ");
		//		break;
		}
		printf("0x%016jX ",phdrs[i].p_offset);
		printf("0x%016jX ",phdrs[i].p_vaddr);
		printf("0x%016jX ",phdrs[i].p_paddr);
		printf("\n                ");
		printf("0x%016jX ",phdrs[i].p_filesz);
		printf("0x%016jX ",phdrs[i].p_memsz);
		printf("%-8X ",phdrs[i].p_flags);
		printf("%7jX ",phdrs[i].p_align);
		printf("\n");
	}
}

