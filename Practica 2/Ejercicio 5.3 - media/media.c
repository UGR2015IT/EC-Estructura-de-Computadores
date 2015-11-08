#include <stdio.h>
#include <stdlib.h>

int lista[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1};
//int lista[]={1,-2,3,-4,5,-6,7,-8,9,-10,11,-12,13,-14,15,-16,17, -18,19,-20,21,-22,23,-24,25,-26,27,-28,29,-30,31,-32}
int longlista = sizeof(lista)/4;
int resto=0;

int media(int* lista, int longlista,int *resto){
	long long suma = 0;
	for (int i=0;i<longlista;i++)
		suma += lista[i];
	*resto = suma % longlista;
	return suma/longlista;
}

int main(){
	printf("resultado en decimal = %d; y el resto es = %d\n", media(lista, longlista,&resto),resto);
	return 0;
}
