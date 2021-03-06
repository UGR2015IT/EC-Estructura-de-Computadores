#include <stdio.h>
#include <stdlib.h>

#define WSIZE 8*sizeof(int)
#define SIZE 8

//unsigned lista[SIZE]={0x80000000,0x00100000, 0x00000800, 0x000000001};
unsigned lista[SIZE]={0x7fffffff,0xffefffff,0xfffff7ff,0xfffffffe,0x01000024,0x00356700,0x8900ac00,0x00bd000ef};

unsigned total_popcount = 0;

int pcount_for(unsigned x) {
	int i;
	int result = 0;
	for (i = 0; i < WSIZE; i++) {
		unsigned mask = 1 << i;
		result += (x & mask) != 0;
	}
	return result;
}

int main(){
	for (int j=0;j<SIZE;j++)
		total_popcount+=pcount_for(lista[j]);
	printf("Il numero totale di bits è: %u", total_popcount);
	return 0;
}
