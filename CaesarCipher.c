#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(char *argv);

void main(int argc, char *argv[]){

	/*	argv[0] = program.c
		argv[1]	= option{-c, -d}
		argv[2] = k
		argv[3] = value of k
		argv[4] = file input
		argv[5] = file output
	*/

	FILE *file_1, *file_2;

	if(! (strcmp(*(argv+1), "-c"))){

		printf("[+]Encypt...\n");
	
	}else if(! (strcmp(*(argv+1), "-d"))){

		printf("[+]Decrypt...\n");
	
	}else{

		error(*	argv);
	}

}

void error(char *argv){

	printf("\n");

	printf("[-] Syntax Error!\n");
	printf("[*] Example:\n");
	printf("Encrypt:\n\t %s -c -k <number> <file_imput> <file_output>\n", (argv));
	printf("Decrypt:\n\t %s -d -k <number> <file_imput> <file_output>\n", (argv));
}