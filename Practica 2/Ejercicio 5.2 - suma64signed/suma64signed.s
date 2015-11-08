# suma.s:	Sumar los N elementos de una lista
#           de enteros con signo

# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista:
	#.int   0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
	.int   0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff
	#.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
	#.int 0x0, 0xffffffff
longlista:
	.int	(.-lista)/4	# .= contador posiciones. Aritmética de etiquetas.
resultado:
	.quad   0x0123456789ABCDEF		# 4B a FF para notar cuándo se modifica cada byte

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
_start:.global _start		# PROGRAMA PRINCIPAL

	mov     $lista, %ebx	# dirección del array lista
	mov  longlista, %ecx	# número de elementos a sumar
	call suma		# llamar suma(&lista, longlista);
	mov  %eax,resultado	# salvar resultado
	mov  %edx,resultado+4

	# void _exit(int status);
	mov $1, %eax		#   exit: servicio 1 kernel Linux
	mov $0, %ebx	# status: código a retornar (0=OK)
	int $0x80		# llamar _exit(0);

suma:
	push     %ebp		                # preservar %ebp (voy a usarlo como indice)
	mov  $0, %ebp                       # poner a 0 índice
	mov  $0, %eax
	mov  $0, %edx                       # poner a 0 acumulador
	mov  $0, %esi
	mov  $0, %edi
bucle:
	mov  (%ebx, %esi, 4), %eax          # %eax = lista[i]
    cdq                                 # sign_extension(%eax)
    add %eax, %esi                      # %esi += %eax
    adc %edx, %edi                      # %edi += %edx
    inc %ebp                            # Incrementar el indice
	cmp %ebp,%ecx			            # comparar con tamaño lista
	jne bucle			                # si no iguales, bucle

    mov %edi, %edx                      # Pongo lor resultados en %edx
    mov %esi, %eax                      # y en %eax

	pop %ebp			# recuperar %ebp antiguo
	ret