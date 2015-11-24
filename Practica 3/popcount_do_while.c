#include <stdlib.h>
#include <stdio.h>

#define WSIZE 8*sizeof(int)
#define SIZE 8

//unsigned lista[SIZE]={0x80000000,0x00100000, 0x00000800, 0x000000001};
unsigned lista[SIZE]={0x7fffffff,0xffefffff,0xfffff7ff,0xfffffffe,0x01000024,0x00356700,0x8900ac00,0x00bd000ef};

unsigned total_popcount = 0;

int pcount_do(unsigned x){
	int result = 0;
	do {
		result += x & 0x1;
		x >>= 1;
	} while (x);
	return result;
}

int main(){
	for (int j=0;j<SIZE;j++)
		total_popcount+=pcount_do(lista[j]);
	printf("Il numero totale di bits è: %u", total_popcount);
	return 0;
}
