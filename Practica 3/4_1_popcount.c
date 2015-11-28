//gcc -m32 -fno-omit-frame-pointer peso_hamming.c -o peso_hamming
#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define TEST 		0
#define WSIZE 8*sizeof(int)

#if ! TEST
	#define SIZE (1<<20)
	unsigned lista[SIZE];
#else
	#define SIZE 4
	unsigned lista[SIZE] = {0x80000000, 0x00100000, 0x00000800, 0x00000001};
	//unsigned lista[SIZE]={0x7fffffff,0xffefffff,0xfffff7ff,0xfffffffe,0x01000024,0x00356700,0x8900ac00,0x00bd000ef};
	//unsigned lista[SIZE]={0x0,0x10204080, 0x3590ac06,0x70b0d0e0, 0xffffffff, 0x12345678, 0x9abcdef0, 0xcafebeef};
	#define RESULT 4
#endif

int resultado=0;


int hamming_for(unsigned* array, int len){
    int i,k;
    int result = 0;
    for (k = 0; k < len; k++)
        for (i = 0; i < WSIZE; i++) {
            unsigned mask = 1 << i;
            result += (array[k] & mask) != 0;
        }
    return result;
}

int hamming_while(unsigned* array, int len){
    int result = 0;
    int i;
    unsigned x;
    for (i = 0; i < len; i++){
        x = array[i];
        while(x){
            result += x & 0x1;
            x >>=1;
        }
    }
    return result;
}

int hamming_asm(unsigned* array, int len){
    int result = 0;
    int i;
    unsigned x;
    for (i = 0; i < len; i++){
        x = array[i];
        asm(
		"\n"
        	"ini3:                             \n\t"
		"shr $0x1, %[x]        \n\t"   //Desplazar afecta a CF ZF
		"adc $0x1, %[r]        \n\t"
		"test %[x], %[x]       \n\t"
		"jnz ini3 "

		: [r] "+r" (result)          // e/s: inicialmente 0, salida valor final
		: [x] "r" (x)               
	);
    }
    return result;
}

int hamming_mask(unsigned *array, int len){
	int result = 0;
	int i,j;
	unsigned x;
	for (i = 0; i < len; i++){
        	x = array[i];
		for (j=0;j<8;j++){
			result += x & 0x1010101;
			x >>= 1;
		}
	}
	result += (result >> 16);
	result += (result >> 8);
	return result & 0xFF;
}

int hamming_SSSE3(unsigned* array, int len){
	int i=0, val=0, result=0;
	int SSE_mask[] = {0x0ff0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f};
	int SSE_LUTb[] = {0x02010100, 0x03020201, 0x03020201, 0x04030302};
	if (len & 0x3) printf("Leyendo 128 bits pero len no multiplo de 4?\n");
	for (;i<len;i+=4){
		asm (
			"movdqu     %[x], %%xmm0 \n\t"
			"movdqa   %%xmm0, %%xmm1 \n\t" // dos copias de x
			"movdqu     %[m], %%xmm6 \n\t" // mascara
			"psrlw       $4 , %%xmm1 \n\t"
			"pand     %%xmm6, %%xmm0 \n\t" //; xmm0 â€“ nibbles inferiores
			"pand     %%xmm6, %%xmm1 \n\t" //; xmm1 â€“ nibbles superiores
			"movdqu     %[l], %%xmm2 \n\t" //; ...como pshufb sobrescribe LUT
"movdqa   %%xmm2, %%xmm3 \n\t" //; ...queremos 2 copias
			"pshufb   %%xmm0, %%xmm2 \n\t" //; xmm2 = vector popcount inferiores
			"pshufb   %%xmm1, %%xmm3 \n\t" //; xmm3 = vector popcount superiores
			"paddb    %%xmm2, %%xmm3 \n\t" //; xmm3 -vector popcount bytes
			"pxor     %%xmm0, %%xmm0 \n\t" //; xmm0 =0,0,0,0
			"psadbw   %%xmm0, %%xmm3 \n\t" //; xmm3 =[pcnt bytes0..7|pcnt bytes8..15]
			"movhlps  %%xmm3, %%xmm0 \n\t" //; xmm0 = [ 0 |pcnt bytes0..7 ]
			"paddd    %%xmm3, %%xmm0 \n\t" //; xmm0 = [ no usado |pcnt bytes0..15]
			"movd     %%xmm0, %[val] \n\t"
			:	[val]	"=r" (val)
			:	[x]	"m" (array[i]),
				[m]	"m" (SSE_mask[0]),
				[l]	"m" (SSE_LUTb[0])
		);
		result +=val;
	}
	return result;
}

// Versión SSE4. 2 (popcount)
int hamming_SSSE4(unsigned* array, int len){
	int i;
	unsigned x;
	int val, result=0;

	for (i=0;i<len;i++){
		x=array[i];
		asm(
			"popcnt %[x], %[val]"
			:	[val] "=r" (val)
			:	[x] "r" (x)
		);
		result+=val;
	}
	return result;
}
// popcount 64bit p/mejorar prestaciones
int hamming_SSSE4_64(unsigned* array, int len){
	int i;
	unsigned x1,x2;
	int val,result=0;
	if (len & 0x1)
		printf( "leer 64b y len impar?\n");
	for (i=0; i<len; i+=2){
		x1 = array[i]; x2 = array[i+1];
		asm(
			"popcnt %[x1], %[val] \n\t"
			"popcnt %[x2], %%edi \n\t"
			"add %%edi, %[val] \n\t"
			: 	[val] "=&r" (val)
			:	[x1] "r" (x1),
				[x2] "r" (x2)
			: "edi"
		);
		result += val;
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
#if ! TEST
	//Inicializar array
	int i;
	for (i=0; i<SIZE; i++)	lista[i]=i;
#endif
	crono(hamming_for, "popcount1 (en lenguaje C for   )");
	crono(hamming_while, "popcount2 (en lenguaje C while  )");
	crono(hamming_asm, "popcount3 (en lenguaje mixto  )");
	crono(hamming_mask, "popcount4 (como en el ejercicio 3.49  )");
	crono(hamming_SSSE3, "popcount5 (con el metodo SSSE3  )");
	crono(hamming_SSSE4, "popcount6 (con el metodo SSSE4  )");
	crono(hamming_SSSE4_64, "popcount7 (con el metodo SSSE4 por 64 bits  )");
#if TEST
	printf("calculado = %d\n", RESULT);
#endif

    exit(0);
}
