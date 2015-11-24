//gcc -m32 -O1 -fno-omit-frame-pointer peso_hamming.c -o peso_hamming
#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define WSIZE 8*sizeof(int)
#define SIZE (1<<20)	// tamaño suficiente para tiempo apreciable
//int lista[SIZE];
int resultado=0;
unsigned lista[4] = {0x80000000, 0x00100000, 0x00000800, 0x00000001};
//unsigned lista[8]={0x7fffffff,0xffefffff,0xfffff7ff,0xfffffffe,0x01000024,0x00356700,0x8900ac00,0x00bd000ef};
//unsigned lista[8]={0x0,0x10204080, 0x3590ac06,0x70b0d0e0, 0xffffffff, 0x12345678, 0x9abcdef0, 0xcafebeef};

int hamming1(unsigned* array, int len){
    int i,k;
    int result = 0;
    for (k = 0; k < 4; k++)
        for (i = 0; i < WSIZE; i++) {
            unsigned mask = 1 << i;
            result += (array[k] & mask) != 0;
        }
    return result;
}

int hamming2(unsigned* array, int len){
    int result = 0;
    int i;
    unsigned x;
    for (i = 0; i < 4; i++){
        x = array[i];
        while(x){
            result += x & 0x1;
            x >>=1;
        }
    }
    return result;
}

int hamming3(unsigned* array, int len){
    int result = 0;
    int i;
    unsigned x;
    for (i = 0; i < 4; i++){
        x = array[i];
        asm("\n"
        "ini3:                             \n\t"
            "shr $0x1, %[x]        \n\t"   //Desplazar afecta a CF ZF
            "adc $0x1, %[r]        \n\t"
            "test %[x], %[x]       \n\t"
            "jnz ini3 "
            
            : [r] "+r" (result)          // e/s: inicialmente 0, salida valor final
            : [x] "r" (x)               ); //Entrada: valor elemento
    }
    return result;
}

void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;	// gettimeofday() secs-usecs
    long           tv_usecs;	// y sus cuentas

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
}

int main(){
    int i;			// inicializar array
    //for (i=0; i<SIZE; i++)	// se queda en cache
      //  lista[i]=i;

    crono(hamming1, "Hamming1 (en lenguaje C for   )");
    crono(hamming2, "Hamming2 (en lenguaje C while  )");

    exit(0);
}
