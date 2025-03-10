section .text

global ft_strcmp

ft_strcmp:
	;prologue
	push	rbp
	mov		rbp, rsp
	;code
	xor		rax, rax; used as an index i

.cmp_char:
	movzx	r8, byte [rsi + rax]; s2[i] saved in reg for cmp 
									; /!\ RBX, RBP, and R12 through R15 are callee-saved so thy must be save dif used
									; /!\ we are manipulating bytes and not int (4bytes) which is the default size.
										;So when manipulating the data we need to specify that => use movzx adds the required zeroes to fill the 64bits register
	cmp		r8b, byte [rdi + rax];  cmp s1[i] and s2[i]
	jne		.return; if != goto .return
	cmp		r8b, 0; else test if end of string reached
	je		.return; if so then .return
	inc		rax; inc i
	jmp		.cmp_char

.return:
	movzx rax, byte [rdi + rax]; return = s1[i]  /!\ still need to specify that we manipulate one byte
	sub		rax, r8; return -= s2[i]
	;epilogue
	pop rbp
	ret