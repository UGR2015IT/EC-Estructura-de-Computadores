#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval


#define SIZE (1<<16) // tamaño suficiente para tiempo apreciable
// unsigned lista[SIZE]={0x80000000, 0x00100000, 0x00000800, 0x00000001};
// unsigned lista[SIZE]={0x7fffffff, 0xffefffff, 0xfffff7ff, 0xfffffffe, 0x01000024, 0x00356700, 0x8900ac00, 0x00bd00ef};
// unsigned lista[SIZE]={0x0	   , 0x10204080, 0x3590ac06, 0x70b0d0e0, 0xffffffff 0x12345678, 0x9abcdef0, 0xcafebeef};


unsigned lista[SIZE];

#define WSIZE (8*sizeof(int))
unsigned parity1(unsigned *array, int len){
  unsigned i;
  int j;
  unsigned result = 0;
  unsigned val = 0;
  unsigned x;

  for(j=0; j<len; j++)
  {
    x = array[j];
    for(i=0; i<WSIZE; i++)
    {
      unsigned mask = 0x1 << i;
      val ^= (x & mask) != 0;
    }

    result += val;
    val = 0;
  }

  return result;
}

unsigned parity2(unsigned *array, int len){
  int j;
  unsigned result = 0;
  unsigned val = 0;
  unsigned x;

  for(j=0; j<len; j++)
  {
    x = array[j];
    do{
      val ^= x & 0x1;
    }while(x >>= 1);

    result += val;
    val = 0;
  }

  return result;
}

unsigned parity3(unsigned *array, int len){
  int j;
  unsigned result = 0;
  unsigned val = 0;
  unsigned x;

  for(j=0; j<len; j++)
  {
    x = array[j];
    while(x)
    {
      val ^= x;
      x >>= 0x1;
    }

    result += (val & 0x1);
    val = 0;
  }

  return result;
}

unsigned parity4(unsigned *array, int len){
  int i;
  unsigned result = 0;
  unsigned val = 0;
  unsigned x;

  for(i=0; i<len; i++)
  {
    x = array[i];
    val = 0;
    asm("\n"
    "ini3:						\n\t"		//seguir mientras que x!=0
    "	xor %[x],%[val]			\n\t"		//realmente solo nos interesa LSB
    "	shr %[x]				\n\t"
    "	test %[x],%[x]			\n\t"
    "	jnz ini3				\n\t"
    "	and $1, %[val]			\n\t"
    : [val]"+r" (val)					//e/s: entrada 0, salida paridad elemento
    : [x] "r" (x)						//entrada: valor elemento
    );

    result += val;
  }

  return result;
}

unsigned parity5(unsigned *array, int len){
  int j, k;
  unsigned x;
  unsigned result = 0;

  for (j=0;j<len;j++)
    {
      x = array[j];

      for (k=16;k>=1;k=k/2)
        x^=(x>>k);

        result += (x&0x1);
      }

      return result;
    }

unsigned parity6(unsigned *array, int len){
  int j;
  unsigned result = 0;
  unsigned x;

  for (j=0;j<len;j++)
    {
      x = array[j];
      asm("\n"
      "mov %[x], %%edx			\n\t" 	//sacar copia para XOR. Controlar el registro edx
      "shr $16, %[x] 				\n\t"
      "xor %[x], %%edx			\n\t"
      "xor %%dh, %%dl				\n\t"
      "setpo %%dl 				\n\t"
      "movzx %%dl, %[x]			\n\t"
      : [x]"+r" (x)			  		//e/s: entrada valor elemento, salida paridad
      :
      :"edx"						  		//clobber
      );

      result += x;
    }
}

void crono(unsigned (*func)(), char* msg){
  unsigned result;
  struct timeval tv1, tv2;  // gettimeofday() secs-usecs
  long           tv_usecs;  // y sus cuentas

  gettimeofday(&tv1, NULL);
  result = func(lista, SIZE);
  gettimeofday(&tv2, NULL);

  tv_usecs = (tv2.tv_sec -tv1.tv_sec)*1E6+
  (tv2.tv_usec-tv1.tv_usec);
  printf("resultado = %d\t", result);
  printf("%s:%9ld us\n", msg, tv_usecs);
}

int main(){
  int i;
  for(i=0; i<SIZE; i++)   // inicializar array
    lista[i]=i; // se queda en cache

  crono(parity1,"parity1 (En C con for    )");
  crono(parity2,"parity2 (En C con while    )");
  crono(parity3,"parity3 (Version resuelta del libro    )");
  crono(parity4,"parity4 (Con bloque asm    )");
  crono(parity5,"parity5 (Parity en arbol del libro    )");
  crono(parity6,"parity6 (arbol en asm    )");
  printf("N*(N+1)/2=%d\n", (SIZE-1)*(SIZE/2));  /*OF*/

  exit(0);
}
