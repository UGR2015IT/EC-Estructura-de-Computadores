# suma.s:	Sumar los elementos de una lista
#		llamando a función, pasando argumentos mediante registros
# retorna: 	código retorno 0, comprobar suma en %eax mediante gdb/ddd

# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista:
	.int	1,2,10, 1,2,0b10, 1,2,0x10	# ejemplos binario 0b / hex 0x
longlista:
	.int	(.-lista)/4	# .= contador posiciones. Aritmética de etiquetas.
resultado:
	.int   -1		# 4B a FF para notar cuándo se modifica cada byte

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
_start:.global _start		# PROGRAMA PRINCIPAL-se puede abreviar de esta forma

	mov     $lista, %ebx	# dirección del array lista
	mov  longlista, %ecx	# número de elementos a sumar
	call suma		# llamar suma(&lista, longlista);
	mov  %eax,resultado	# salvar resultado
				# void _exit(int status);
	mov $1, %eax		#   exit: servicio 1 kernel Linux
	mov $0, %ebx		# status: código a retornar (0=OK)
	int $0x80		# llamar _exit(0);

# SUBRUTINA:	suma(int* lista, int longlista);
# entrada:	1) %ebx = dirección inicio array
#		2) %ecx = número de elementos a sumar
# salida: 	   %eax = resultado de la suma

suma:
	push     %edx		# preservar %edx (se usa aquí como índice)
	mov  $0, %eax		# poner a 0 acumulador
	mov  $0, %edx		# poner a 0 índice
bucle:
	add  (%ebx,%edx,4), %eax	# acumular i-ésimo elemento
	inc      %edx			# incrementar índice
	cmp %edx,%ecx			# comparar con longitud
	jne bucle			# si no iguales, seguir acumulando

	pop %edx			# recuperar %edx antiguo
	ret
