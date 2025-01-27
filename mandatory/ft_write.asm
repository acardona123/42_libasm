section .data
	SYSCALL_WRITE equ 1

section .text

extern __errno_location
global ft_write

ft_write:
	;write syscall
	mov eax, SYSCALL_WRITE
	;the args for the write syscall are the same as the ones of ft_write
	syscall
	;error detection
	cmp eax, 0
	jge .return
	;error management
.set_errno:
	neg rax
	mov rdi, rax
	; call __errno_location
	call qword [rel __errno_location wrt ..got]; /!\ for security reasons we want to authorized the code to be PIE (position-independent executable)[the pgm does not have to be in a specific address to work]. Because of that the address of __errno_location has to be relative to the GOT (Global offset table)[stores the address of the exernal symboles(var & functions)]
	mov [rax], rdi
	mov rax, -1
.return:
	ret
	;rtn
