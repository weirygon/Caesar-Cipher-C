#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertInt(char *argv);
int simplifyNumber(int n);
void encrypt(FILE *in, int key, FILE *out);
void decrypt(FILE *in, int key, FILE *out);
int isNumber(char *argv);
int syntax(char **argv);
void error(char *argv);

void main(int argc, char *argv[]){

	/*	argv[0] = program
		argv[1]	= option{-c, -d}
		argv[2] = k OR n
		argv[3] = value of argv[2]
		argv[4] = file input
		argv[5] = file output
	*/

	FILE *file_in, *file_out;

	int key = 0;
	int opt = syntax((argv));

	switch(opt){
		case 1:

			printf("[+]Encypt...\n");
			file_in = fopen(argv[4], "r");
			
			if(!file_in){
				printf("[-]The file %s cannot be open!\n", argv[4]);
				exit(1);
			}

			file_out = fopen(argv[5], "w");

			if(!file_out){

				printf("[-] The file %s cannot be create!\n", argv[5]);
				exit(1);
			}

			key = convertInt(argv[3]);
			key = simplifyNumber(key);

			encrypt(file_in, key, file_out);
			
			fclose(file_in);
			fclose(file_out);
			file_in = NULL;
			file_out = NULL;

		break;

		case 2:
			printf("[+]Decrypt...\n");
			file_in = fopen(argv[4], "r");
			
			if(!file_in){
				printf("[-]The file %s cannot be open!\n", argv[4]);
				exit(1);
			}

			file_out = fopen(argv[5], "w");

			if(!file_out){
				printf("[-] The file %s cannot be create!\n", argv[5]);
				exit(1);
			}

			key = convertInt(argv[3]);

			decrypt(file_in, key, file_out);
			
			fclose(file_in);
			fclose(file_out);
			file_in = NULL;
			file_out = NULL;

		break;

		default:
			error(*argv);
	}

}

int convertInt(char *argv){

	int aux = 0;

	for(int i=0; argv[i] != 0; i++){

		argv[i] =argv[i] - 48;

		if(!i)	//i == 0
			aux = argv[i];
		else{
			
			aux = aux * 10;
			aux = aux + argv[i];

		}
	}
	
	return aux;

}

int simplifyNumber(int n){

	while(n > 26)
		n -= 26;

	return n;
	
}

void encrypt(FILE *in, int key, FILE *out){

	char aux;

	while( !(feof(in)) ){

		fscanf(in, "%c", &aux);

		if( (aux > 64) && (aux < 91)){ //Uppercase

			aux = aux + key;

			if(aux > 90)
				aux -= 26;

		}else if( (aux > 96) && (aux < 123)){ //Downcase

			aux = aux + key;

			if(aux > 122)
				aux -= 26;

			if(aux < 0){
				aux = aux + 128;
				aux += 5;
				aux += 97;

			}
				
		}

		fprintf(out, "%c", aux);
	}
}

void decrypt(FILE *in, int key, FILE *out){

	char aux;

	while( !(feof(in)) ){

		fscanf(in, "%c", &aux);

		if( (aux > 64) && (aux < 91)){ //Uppercase

			aux = aux - key;

			while(aux < 65)
				aux += 26;

		}else if( (aux > 96) && (aux < 123)){ //Downcase

			aux = aux - key;

			while( (aux < 97) ){

				aux += 26;
			}
		}

		fprintf(out, "%c", aux);
	}

}

int isNumber(char *argv){

	for(int i=0; argv[i]!= 0; i++){

		if(argv[i] < 48 || argv[i] > 57)
			return 0;
	}

	return 1;

}

int syntax(char **argv){

	for(int i=0; i<6; i++){
		if(!(argv[i]))
			return -1;
	}

	
	if( !(strcmp(argv[1], "-c")) ){

		if( !(strcmp(argv[2], "-k")) || !(strcmp(argv[2], "-n"))){
			
			if(isNumber(argv[3]))
				return 1;
			else
				return -1;

		}
	
	}else if( !(strcmp(argv[1], "-d")) ){

		if( !(strcmp(argv[2], "-k")) || !(strcmp(argv[2], "-n"))){

			if(isNumber(argv[3]))
				return 2;
			else
				return -1;

		}

	}else
		return -1;

}

void error(char *argv){

	printf("\n");

	printf("[-] Syntax Error!\n");
	printf("[*] Example:\n");
	printf("Encrypt:\n\t %s -c -k <number> <file_imput> <file_output>\n", (argv));
	printf("Decrypt:\n\t %s -d -k <number> <file_imput> <file_output>\n", (argv));
}
