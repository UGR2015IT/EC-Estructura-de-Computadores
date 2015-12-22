//gcc -m32 bomba_davide_gallitelli.c -o bomba_DavideGallitelli

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

char password[]="ockzesqlvxlt";
int passcode = 5216;

void boom(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void defused(){
	printf("*************************\n");
	printf("*** bomba desactivada ***\n");
	printf("*************************\n");
	exit(0);
}

void encrypt_pass(char* text){
	int i=0;
	int lenght = strlen(text)-1;
	for (i=0;i<lenght;i++)	text[i]=text[i]+i;
}

int encrypt_code(int code){
	return (code + 1995);
}

int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
#define TLIM 60
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);

	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);
	encrypt_pass(pass);
	if (strncmp(pass,password,strlen(password)))
	    boom();

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
	    boom();

	printf("Introduce el código: ");
	scanf("%i",&pasv);
	if (encrypt_code(pasv)!=passcode) boom();

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
	    boom();

	defused();
}
