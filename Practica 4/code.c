#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()

void encrypt_pass(char* text){
	int i, lenght = strlen(text)-1, half = lenght/2;
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
	int myCode;
	char pass[100];
	printf("Introduce la contrasena: ");
	fgets(pass,100,stdin);
	printf("Introduce el código: ");
	scanf("%i",&myCode);
	encrypt_pass(pass);
	myCode = encrypt_code(myCode);
	printf("Contrasena CRIPTADA: %s \n", &pass);
	printf("Codigo CRIPTADO: %d \n",myCode);
}
