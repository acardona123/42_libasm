section .text

global ft_strlen

ft_strlen:
;function prologue
	push	rbp
	mov		rbp, rsp
	xor		rax, rax ;setting results to 0
;code
.next:
	cmp		[rdi + rax], byte 0
	je		.return
	inc		rax
	jmp		.next

;epilogue
.return:
	pop		rbp
	ret