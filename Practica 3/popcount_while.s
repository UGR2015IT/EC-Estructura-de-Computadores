popcount:

	push 		%edx
	movl	    $1, %edx
	movl	    $0, %esi
	
	testl	   %ebx,%ebx
	je go_out

	loop:
		movl 		%ebx, %eax
		andl 		  $1, %eax
		add 		%eax, %ecx
		shrl 		      %ebx
		jne loop
	go_out:
		pop 		      %edx
		ret
