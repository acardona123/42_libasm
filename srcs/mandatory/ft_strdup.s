section .bss
	dest RESD 1 ; static (because not global) var stored in the program data segment (lifetime of the entire pgm). Not optimized here as registers could have been used (faster and less resources) (only pedagogic use)
	
section .text

	global ft_strdup
	extern malloc
	extern ft_strlen
	extern ft_strcpy

ft_strdup:
	push rbp
	mov rbp, rsp
	mov qword [rel dest], rdi
.getLen:
	call qword [rel ft_strlen wrt ..got]
.allocate_mem:
	inc rax
	mov rdi, rax
	;checking stack alignment:
		;after ft_strdup call the stack was 16 - 8 bytes aligned (return pointer pushed to the stack)
		;after push rpb we are 8-8o aligned which is 16o aligned
		;=> alignement ok
	call qword [rel malloc wrt ..got]
	cmp rax, byte 0
	je .return
	mov rdi, rax
	mov rsi, qword [rel dest]
.cpy:
	call qword [rel ft_strcpy wrt ..got]
.return:
	pop rbp
	add rsp , 4; de-allocate mem of local var dest
	ret
