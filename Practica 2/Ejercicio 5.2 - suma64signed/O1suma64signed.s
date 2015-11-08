	.file	"suma64signed.c"
	.text
	.globl	suma
	.type	suma, @function
suma:
.LFB38:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	16(%esp), %ecx
	movl	20(%esp), %eax
	testl	%eax, %eax
	jle	.L4
	movl	%ecx, %edi
	leal	(%ecx,%eax,4), %esi
	movl	$0, %eax
	movl	$0, %edx
.L3:
	movl	(%edi), %ecx
	movl	%ecx, %ebx
	sarl	$31, %ebx
	addl	%ecx, %eax
	adcl	%ebx, %edx
	addl	$4, %edi
	cmpl	%esi, %edi
	jne	.L3
	jmp	.L2
.L4:
	movl	$0, %eax
	movl	$0, %edx
.L2:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE38:
	.size	suma, .-suma
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"resultado en decimal =%llu\n"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC1:
	.string	"resultado en hexadecimal =%llx\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$4, %esp
	pushl	longlista
	pushl	$lista
	call	suma
	addl	$8, %esp
	pushl	%edx
	pushl	%eax
	pushl	$.LC0
	pushl	$1
	call	__printf_chk
	addl	$8, %esp
	pushl	longlista
	pushl	$lista
	call	suma
	addl	$16, %esp
	pushl	%edx
	pushl	%eax
	pushl	$.LC1
	pushl	$1
	call	__printf_chk
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.globl	longlista
	.data
	.align 4
	.type	longlista, @object
	.size	longlista, 4
longlista:
	.long	32
	.globl	lista
	.align 32
	.type	lista, @object
	.size	lista, 128
lista:
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
