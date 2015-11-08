	.file	"suma64signed.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
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
	movl	20(%esp), %eax
	testl	%eax, %eax
	jle	.L4
	movl	16(%esp), %edi
	xorl	%edx, %edx
	leal	(%edi,%eax,4), %esi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%edi), %ecx
	movl	%ecx, %ebx
	sarl	$31, %ebx
	addl	%ecx, %eax
	adcl	%ebx, %edx
	addl	$4, %edi
	cmpl	%esi, %edi
	jne	.L3
.L2:
	popl	%ebx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
.L4:
	.cfi_restore_state
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L2
	.cfi_endproc
.LFE38:
	.size	suma, .-suma
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"resultado en decimal =%llu\n"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC2:
	.string	"resultado en hexadecimal =%llx\n"
	.section	.text.unlikely
.LCOLDB3:
	.section	.text.startup,"ax",@progbits
.LHOTB3:
	.p2align 4,,15
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
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x70,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x6,0x2,0x75,0x78
	.cfi_escape 0x10,0x3,0x2,0x75,0x74
	subl	$8, %esp
	movl	longlista, %edi
	testl	%edi, %edi
	jle	.L13
	sall	$2, %edi
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L10:
	movl	lista(%esi), %eax
	cltd
	addl	%eax, %ecx
	adcl	%edx, %ebx
	addl	$4, %esi
	cmpl	%edi, %esi
	jne	.L10
.L9:
	pushl	%ebx
	pushl	%ecx
	pushl	$.LC1
	pushl	$1
	call	__printf_chk
	movl	longlista, %edi
	addl	$16, %esp
	testl	%edi, %edi
	jle	.L14
	sall	$2, %edi
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L12:
	movl	lista(%esi), %eax
	cltd
	addl	%eax, %ecx
	adcl	%edx, %ebx
	addl	$4, %esi
	cmpl	%esi, %edi
	jne	.L12
.L11:
	pushl	%ebx
	pushl	%ecx
	pushl	$.LC2
	pushl	$1
	call	__printf_chk
	addl	$16, %esp
	leal	-16(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	.cfi_remember_state
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
.L13:
	.cfi_restore_state
	xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	jmp	.L9
.L14:
	xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	jmp	.L11
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE3:
	.section	.text.startup
.LHOTE3:
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
