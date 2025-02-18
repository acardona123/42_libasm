section .data
	check_base_forbidden_char db "+- \f\n\r\t\v"
	whitespace_char db " \f\n\r\t\v"

section .bss
	ascii_char	resb 128

section .text

	global ft_atoi_base
	global check_base
	global trim_whitespaces
	global set_sign
	extern get_absolute_value


ft_atoi_base:
	push rbp
	mov rbp, rsp

	push r10		;callee saved reg
	push r11		;callee saved reg
	push r12		;callee saved reg
	mov r10, rdi	;store str
	mov r11, rsi	;store base

	;call check_base on base
	cmp rdi, 0
	je .atoi_base_error_return
	cmp rsi, 0
	je .atoi_base_error_return

	.atoi_check_base_validity:
		mov rdi, r11
		;stack alignment: ok
		call check_base
		cmp rax, 0
		jne .atoi_base_error_return
	.atoi_trim_whitespaces_in_str:
		mov rdi, r10
		call trim_whitespaces
		mov r10, rax
	.atoi_set_sign:
		;store str in the stack to be abe to give its address as an argument
		sub rsp, 8		;allocate mem on the stack
		mov [rsp], r10
		mov rdi, rsp
		call set_sign
		mov r12, rax	;store sign
		mov r10, [rsp]	;retrieve str trimmed from its +- prefixes
		add rsp, 8		;clean memory
	.atoi_get_absolute_value:
		mov rdi, r10
		mov rsi, r11
		call get_absolute_value
	imul r12	;multiply the result (the absolute value) by he sign
	
.atoi_base_return:
	pop r12
	pop r11
	pop r10
	pop rbp
	ret
.atoi_base_error_return:
	mov rax, 0
	jmp	.atoi_base_return


check_base:
	; push rbp
	; mov rbp, rsp

	.init_present_char:
		mov r8, rdi	;save base
		mov rdi, 1
		call check_base_update_ascii
		mov rdi, r8
		; xor rcx, rcx						;init for loop index
		; .for_loop_start:
		; 	cmp rcx, 8
		; 	jge .check_duplicates_or_forbidden
		; 	lea rdx, [rel check_base_forbidden_char]
		; 	add rdx, rcx
		; 	movzx rsi, byte [rdx]		;Move with Zero-Extend to get forbidden_char[i]
		; 	lea rdx, [rel ascii_char]
		; 	add rdx, rsi
		; 	mov byte [rdx], 1
		; 	inc rcx
		; 	jmp .for_loop_start
	.check_duplicates_or_forbidden:
		xor rcx, rcx	;init while loop index
		mov rdx, rdi	;store base to inc it
		.while_loop_start:
			cmp rcx, 128
			jge .check_base_size
			movzx rsi, byte [rdx]			;get base[i]
			cmp rsi, 0				
			je .check_base_size

			lea r8, [rel ascii_char]
			add rsi,  r8	;get present_char + base[i]
			cmp byte [rsi], 1
			je .check_base_error
			mov byte [rsi], 1
			inc rcx
			inc rdx
			jmp .while_loop_start
	.check_base_size:
		cmp rdx, 1
		jle .check_base_error
		cmp rdx, 128
		je .check_base_error
		mov rax, 0
	.check_base_return:
		.reset_ascii_char:
			mov rdi, 0
			call check_base_update_ascii
		; pop rbp
		; mov rbp, rsp
		ret
	.check_base_error:
		mov rax, 1
		jmp .check_base_return

check_base_update_ascii:
	; push rbp
	; mov rbp, rsp
	xor rcx, rcx						;init for loop index
	.for_loop_start:
		cmp rcx, 8
		jge .check_base_update_ascii_ret
		lea rdx, [rel check_base_forbidden_char]
		add rdx, rcx
		movzx rsi, byte [rdx]		;Move with Zero-Extend to get forbidden_char[i]
		lea rdx, [rel ascii_char]
		add rdx, rsi
		mov byte [rdx], dil
		inc rcx
		jmp .for_loop_start
	.check_base_update_ascii_ret:
	; pop rbp
	; mov rbp, rsp
		ret


trim_whitespaces:
	; push rbp
	; mov rbp, rsp

	call trim_whitespaces_update_ascii
	.trim_first_loop:
		cmp [rdi], byte 0
		je .trim_whitespaces_ret
		movzx rax, byte [rdi]
		lea rdx, [rel ascii_char]
		cmp byte [rdx + rax], 1
		jne .trim_whitespaces_ret
		inc rdi
		jmp .trim_first_loop
	.trim_whitespaces_ret:
	mov rax, rdi
	; pop rbp
	; mov rbp, rsp
	ret


trim_whitespaces_update_ascii:
	; push rbp
	; mov rbp, rsp
	xor rcx, rcx						;init for loop index
	.trim_loop_start:
		cmp rcx, 6
		jge .trim_whitespaces_update_ascii_ret
		lea rdx, [rel whitespace_char]
		add rdx, rcx
		movzx rsi, byte [rdx]		;Move with Zero-Extend to get forbidden_char[i]
		lea rdx, [rel ascii_char]
		add rdx, rsi
		mov byte [rdx], 1
		inc rcx
		jmp .trim_loop_start
	.trim_whitespaces_update_ascii_ret:
	; pop rbp
	; mov rbp, rsp
		ret


set_sign:
	; push rbp
	; mov rbp, rsp
	.count_minus_char:
		xor rax, rax	;count number of - signs
		.sign_while:
			.sign_while_tests:
				mov rsi, [rdi]	; get *str
				movzx rsi, byte [rsi]	; get **str
				cmp rsi, 0
				je .deduce_sign_from_minus_count
				cmp rsi, '-'
				je .minus_char
				cmp rsi, '+'
				je .all_char
				jmp .deduce_sign_from_minus_count
			.sign_while_content:
				.minus_char:
					xor rax, 1
				.all_char:
					inc DWORD [rdi]
					jmp .sign_while
	.deduce_sign_from_minus_count:
		; pop rbp
		; mov rbp, rsp
		cmp rax, 0
		je .sign_pos
		.sign_neg:
			mov rax, -1
			ret
		.sign_pos:
			mov rax, 1
			ret



; get_absolute_value:
; 	push rbp
; 	mov rbp, rsp



; 	pop rbp
; 	mov rbp, rsp