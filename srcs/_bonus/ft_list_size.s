;int ft_list_size(t_list *begin_list)

section .text
global ft_list_size

ft_list_size:
	xor	rax, rax
.loop:
	cmp	rdi, byte 0
	je	.return
	inc	rax
	mov	rdi, [rdi + 8]
	jmp	.loop
.return:
	ret
