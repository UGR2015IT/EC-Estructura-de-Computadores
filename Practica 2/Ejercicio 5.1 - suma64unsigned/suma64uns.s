# suma.s:	Sumar los N elementos de una lista en binario natural
#           sin signo de 32 bits sin perder digitos.
#           La suma va a utilisar mas de 32 bits.

# =========================================================
# SECCIÓN DE DATOS (.data, variables globales inicializadas)

.section .data
lista:
	.int	0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000,0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
	#.int   0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
	#.int	0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000, 0x8000000
longlista:
	.int	(.-lista)/4	# .= contador posiciones. Aritmética de etiquetas.
resultado:
	.quad   0x0123456789ABCDEF          #64 bits resultado, para ver cuando se modifica cada byte

# ===============================================
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)

.section .text
_start:.global _start

	mov     $lista, %ebx	# dirección del array lista
	mov  longlista, %ecx	# número de elementos a sumar
	call suma		        # llamar suma(&lista, longlista);
	mov  %eax,resultado	    # salvar resultado
	mov  %edx,resultado+4

	#Llamada al sistema WRITE
	#		ssize_t  write(int fd, const void *buf, size_t count);
	mov $4, %eax		# write: servicio 4 kernel Linux
	mov $1, %ebx		#    fd: descriptor de fichero para stdout
	mov resultado, %ecx	#   buf: dirección del texto a escribir
	mov $8, %esi		# count: número de bytes a escribir
	int $0x80		    # llamar write

	# void _exit(int status);
	mov $1, %eax		#   exit: servicio 1 kernel Linux
	mov $0, %ebx	    # status: código a retornar (0=OK)
	int $0x80		    # llamar _exit(0);

suma:
	push     %esi		# preservar %esi (que voy a usar como índice)
	mov  $0, %eax		# poner a 0 el acumulador %eax
	mov  $0, %esi		# poner a 0 el índice %esi
	xor  %edx, %edx		# poner a 0 %edx
	xor %edi, %edi
bucle:
	add (%ebx, %esi,4), %eax
	adc $0, %edx			# acumular i-esimo elemento
	inc      %esi			# incrementar el índice
	cmp %esi,%ecx			# comparar con tamaño lista
	jne bucle			    # si no iguales, bucle

	pop %esi			    # recuperar %esi antiguo
	ret
