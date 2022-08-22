#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int syntax(char **argv);
int isNumber(char *argv);
void error(char *argv);

void main(int argc, char *argv[]){

	/*	argv[0] = program
		argv[1]	= option{-c, -d}
		argv[2] = k OR n
		argv[3] = value of argv[2]
		argv[4] = file input
		argv[5] = file output
	*/

	FILE *file_1, *file_2;

	int opt = syntax((argv));

	switch(opt){
		case 1:
			printf("[+]Encypt...\n");
		break;

		case 2:
			printf("[+]Decrypt...\n");
		break;

		default:
			error(*argv);
	}

}

int syntax(char **argv){

	
	if( !(strcmp(argv[1], "-c")) ){

		if( !(strcmp(argv[2], "-k")) || !(strcmp(argv[2], "-n"))){
			
			if(isNumber(argv[3]))
				return 1;
			else
				return 0;

		}
	
	}else if( !(strcmp(argv[1], "-d")) ){

		if( !(strcmp(argv[2], "-k")) || !(strcmp(argv[2], "-n"))){
			
			if(isNumber(argv[3]))
				return 1;
			else
				return 0;

		}

	}else
		return -1;


}

int isNumber(char *argv){

	for(int i=0; argv[i]!= 0; i++){

		if(argv[i] < 48 || argv[i] > 57)
			return 0;
	}

	return 1;

}

void error(char *argv){

	printf("\n");

	printf("[-] Syntax Error!\n");
	printf("[*] Example:\n");
	printf("Encrypt:\n\t %s -c -k <number> <file_imput> <file_output>\n", (argv));
	printf("Decrypt:\n\t %s -d -k <number> <file_imput> <file_output>\n", (argv));
}
