section .text

global ft_strcmp

ft_strcmp:
	;prologue
	push rbp
	mov rbp, rsp
	;code
	xor rax, rax; used as an index i

.cmp_char:
	movzx	r10, byte [rsi + rax]; s1[i] saved in reg for cmp   /!\ we are manipulating bytes and not int (4bytes) which is the default size. So when manipulating the data we need to specify that => use movzx adds the required zeroes to fill the 64bits register
	cmp		r10b, byte [rdi + rax];  cmp s1[i] and s2[i]
	jne		.return; if != goto .return
	cmp		r10b, 0; else test if end of string reached
	je		.return; if so then .return
	inc		rax; inc i
	jmp		.cmp_char

.return:
	movzx rax, byte [rdi + rax]; return = s1[i]  /!\ still need to specify that we manipulate one byte
	sub rax, byte r10; return -= s2[i]
	;epilogue
	pop rbp
	ret