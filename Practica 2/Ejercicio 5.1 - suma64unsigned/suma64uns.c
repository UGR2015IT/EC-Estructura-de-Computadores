#include <stdio.h>
#include <stdlib.h>

unsigned lista[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//unsigned lista[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17, 18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}
int longlista = sizeof(lista)/4;

unsigned long long suma (unsigned* lista, int longlista){
	unsigned long long sum=0;
	for (int i=0;i<longlista;i++)
		sum+=lista[i];
	return sum;
};

int main(){
	printf("resultado en decimal =%llu\n", suma(lista, longlista));
	printf("resultado en hexadecimal =%llx\n", suma(lista, longlista));
	return 0;
}
