#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

char password[]="ohutkqtg}ohu";
int  passcode  = 10203050;

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
	int i=0, lenght = strlen(text)-1, half = lenght/2;
	char temp;
	for (i=0;i<lenght/2;i++){
		temp = text[lenght-i-1];
		text[lenght-i-1] = text[i]+half;
		text[i] = temp+half;
	}
}

int encrypt_code(int code){
	int temp = code, result = 0, i=1;
	while (temp != 0){
		result += temp % 10 * power(10,i);
		temp = temp / 10;
		i=i+2;
	}
	return result;
}

int power(int number, int power){
	int i = 1, value = number;
	for (i=1;i<power;i++) value = value * number;
	return value;
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
