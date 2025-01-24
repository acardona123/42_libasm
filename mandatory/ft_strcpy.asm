section .text

global ft_strcpy

ft_strcpy:
	;prologue
	push rbp
	mov rbp, rsp
	;code
	xor rax, rax; used as an index i

.cpy_char:
	movzx	r10, byte [rsi + rax]; s1[i] saved in reg for cmp   /!\ we are manipulating bytes and not int (4bytes) which is the default size. So when manipulating the data we need to specify that => use movzx adds the required zeroes to fill the 64bits register
	mov		[rdi + rax], byte r10;  cmp s1[i] and s2[i]
	cmp		r10b, 0; else test if end of string reached
	je		.return; if so then .return
	inc		rax; inc i
	jmp		.cpy_char

.return:
	mov rax, rdi
	;epilogue
	pop rbp
	ret