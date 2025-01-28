section .bss
	dest RESD 1
	
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
	call qword [rel malloc wrt ..got]
	mov rdi, rax
	mov rsi, qword [rel dest]
	cmp rax, byte 0
	je .return
.cpy:
	call qword [rel ft_strcpy wrt ..got]
.return:
	pop rbp
	ret
