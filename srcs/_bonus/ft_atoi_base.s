section .data
	check_base_forbidden_char db "+- ",9, 10, 11, 12, 13, 0		;"+- \f\n\r\t\v"
	whitespace_char db " ", 9, 10, 11, 12, 13, 0		;" \f\n\r\t\v"

section .bss
	ascii_char	resb 128

section .text
	global ft_atoi_base

ft_atoi_base:
	push rbp
	mov rbp, rsp

	push	r12			;callee saved reg
	push	r13			;callee saved reg
	push	r14			;callee saved reg
	mov		r12, rdi	;store str
	mov		r13, rsi	;store base

	;call check_base on base
	cmp	rdi, 0
	je	.atoi_base_error_return
	cmp	rsi, 0
	je	.atoi_base_error_return

	.atoi_check_base_validity:
		mov		rdi, r13

		sub		rsp, 8		;stack alignment
		call	check_base
		add		rsp, 8
		cmp		rax, 0
		jne		.atoi_base_error_return
	.atoi_trim_whitespaces_in_str:
		mov		rdi, r12
		call	trim_whitespaces
		mov		r12, rax
	.atoi_set_sign:
		;store str in the stack to be abe to give its address as an argument
		sub		rsp, 8			;allocate mem on the stack
		mov		[rsp], r12		;*rsp = str
		mov		rdi, rsp
		sub		rsp, 8			;stack alignment
		call	set_sign
		mov		r14, rax		;store sign
		mov		r12, [rsp + 8]	;retrieve the updated str
		add		rsp, 16			;clean memory
	.atoi_get_absolute_value:
		mov		rdi, r12
		mov		rsi, r13
		call	get_absolute_value
	imul 	r14				;multiply the result (the absolute value) by he sign, store result in rax and (rdx if result size > 64 bits)
	.atoi_base_return:
		pop	r14
		pop	r13
		pop	r12
		mov	rsp, rbp
		pop	rbp
		ret
	.atoi_base_error_return:
		mov	rax, 0
		jmp	.atoi_base_return


check_base:
	; push rbp
	; mov rbp, rsp
	.init_present_char:
		push	rdi	;save base
		sub		rsp, 8
		mov		rdi, 0
		call	reset_ascii
		call	put_base_forbidden_char_in_ascii
		add		rsp, 8
		pop		rdi
	.check_duplicates_or_forbidden:
		lea rdx, [rel ascii_char]
		xor rcx, rcx	;init while loop index
		.while_loop_start:
			cmp rcx, 128			;if len(base) > 128 (ascii table size) there will be duplicates so we stop
			jge .check_base_size
			movzx rsi, byte [rdi + rcx]	;get base[i]
			cmp rsi, 0				;check if base[i] = 0 ie if we checked all base's chars
			je .check_base_size

			add rsi,  rdx		;get present_char + base[i]
			cmp byte [rsi], 1
			je .check_base_error
			mov byte [rsi], 1
			inc rcx
			jmp .while_loop_start
	.check_base_size:
		cmp rcx, 1
		jle .check_base_error
		cmp rcx, 128
		je .check_base_error
		mov rax, 0
	.check_base_return:
		; mov esp, ebp
		; pop rbp
		ret
	.check_base_error:
		mov rax, 1
		jmp .check_base_return

;void put_base_forbidden_char_in_ascii(void)
put_base_forbidden_char_in_ascii:
	; push rbp
	; mov rbp, rsp
	lea r10, [rel check_base_forbidden_char]
	lea r11, [rel ascii_char]
	xor rcx, rcx						;init for loop index
	.for_loop_start:
		cmp rcx, 8
		jge .put_base_forbidden_char_in_ascii_ret
		movzx rsi, byte [r10 + rcx]		;Move with Zero-Extend to get forbidden_char[i]
		mov byte [r11 + rsi], 1			;ascii_char[forbidden_char[i]] = 1
		inc rcx
		jmp .for_loop_start
	.put_base_forbidden_char_in_ascii_ret:
		; mov esp, ebp
		; pop rbp
		ret


; char *trim_whitespaces(char *str)
trim_whitespaces:
	; push rbp
	; mov rbp, rsp
	.trim_set_ascii_table:
		push	rdi		;save str
		sub		rsp, 8	;stack_alignment
		mov		rdi, 0
		call	reset_ascii
		call	trim_whitespaces_update_ascii
		add		rsp, 8
		pop		r8	;retrieve str
	lea	rdx, [rel ascii_char]
	.trim_first_loop:
		cmp [r8], byte 0
		je .trim_whitespaces_ret
		movzx rax, byte [r8]
		cmp byte [rdx + rax], byte 1
		jne .trim_whitespaces_ret
		inc r8
		jmp .trim_first_loop
	.trim_whitespaces_ret:
		mov rax, r8
		; mov esp, ebp
		; pop rbp
		ret

; void reset_ascii(char reset_value)
reset_ascii:
	lea rsi, [rel ascii_char]
	xor rcx, rcx
	.reset_ascii_loop:
		cmp rcx, 128
		jge .reset_ascii_ret
		mov byte [rsi + rcx], dil
		inc rcx
		jmp .reset_ascii_loop
	.reset_ascii_ret:
		ret

; void trim_whitespaces_update_ascii( void )
trim_whitespaces_update_ascii:
	; push rbp
	; mov rbp, rsp
	lea rdi, [rel whitespace_char]
	lea rsi, [rel ascii_char]
	xor rcx, rcx						;init for loop index
	.trim_loop_start:
		cmp rcx, 6
		jge .trim_whitespaces_update_ascii_ret
		movzx rdx, byte [rcx + rdi]		;Move with Zero-Extend to get whitespace_char[i]
		mov byte [rsi + rdx], 1			;ascii_char[whitespace_char[i]] = 1
		inc rcx
		jmp .trim_loop_start
	.trim_whitespaces_update_ascii_ret:
		; mov esp, ebp
		; pop rbp
		ret


; int set_sign(char **str)
set_sign:
	; push rbp
	; mov rbp, rsp
	.count_minus_char:
		xor rcx, rcx	;count number of - signs
		.sign_while:
			.sign_while_tests:
				mov		rsi, [rdi]			; rsi = *str
				movzx	rsi, byte [rsi]		; get **str
				cmp		rsi, 0
				je		.deduce_sign_from_minus_count
				cmp		rsi, '-'
				je		.minus_char
				cmp		rsi, '+'
				je		.all_char
				jmp		.deduce_sign_from_minus_count
			.sign_while_content:
				.minus_char:
					xor rcx, 1
				.all_char:
					inc qword [rdi]
					jmp .sign_while
	.deduce_sign_from_minus_count:
		; pop rbp
		cmp rcx, 0
		je .sign_pos
		.sign_neg:
			mov rax, -1
			ret
		.sign_pos:
			mov rax, 1
			ret


;int get_absolute_value(char *str, char *base)
get_absolute_value:
	push	rbp
	mov		rbp, rsp

	push	r12
	push	r13
	mov		r12, rdi	;save str
	mov		r13, rsi	;save base
	.get_abs_set_ascii_table:
		;reset fill ascii_char with -1
		mov		rdi, -1
		call	reset_ascii
		;call of set_base_chars_values
		mov		rdi, r13				;arg1 = base
		call	set_base_chars_values
	.get_abs_calculate_str_value:
		mov		rdi, r12				;arg1 = str
		mov		rsi, rax				;arg2 = len(base) = ret of set_base_chars_values
		call	calculate_str_value
	pop r13
	pop r12
	mov rsp, rbp
	pop rbp
	ret


;int get_abs_set_base_chars_values(char *base) ; return len(base)
;set the values of each char of the base
set_base_chars_values:
	; push rbp
	; mov rbp, rsp
	lea	rdx, [rel ascii_char]
	xor	rcx, rcx							;init for loop index i
	.set_base_chars_values_loop:
		movzx	rsi, byte [rdi + 1 * rcx]	;get base[i]
		cmp		rsi, 0
		je		.set_base_chars_values_ret
		mov		byte [rdx + rsi], cl			;ascii_char[base[i]] = i
		inc		rcx
		jmp		.set_base_chars_values_loop
	.set_base_chars_values_ret:
		; mov rsp, rbp
		; pop rbp
		mov	rax, rcx
		ret				;return i = len(base)


; int calculate_str_value(char *str, int len_base), char *ascii_char is global
calculate_str_value:
	lea	r8, [rel ascii_char]				;load the values of each char compared to the base (/!\ rax and rdx are gonna be affected by mul, can't be used there)
	xor	rax, rax							;abs_val
	.calculate_str_value_loop:
		movzx	rcx, byte [rdi]				; get *str
		cmp		rcx, 0
		je		.calculate_str_value_ret
		movzx	r9, byte [r8 + rcx]			;ascii_char[*str]
		cmp		r9, 0xff					; == -1?
		je		.calculate_str_value_ret
		mul 	rsi							;abs_val *= len_base
		add 	rax, r9						;abs_val += ascii_char[*str]
		inc		rdi							;++str
		jmp		.calculate_str_value_loop
	.calculate_str_value_ret:
		ret



; ========================================================================================
; 								Similar c code
; ========================================================================================


; int ft_atoi_base(char *str, char *base)
; {
; 	int 			sign;
; 	unsigned int	absolute_value;

; 	if (check_base(base))
; 	{
; 		printf("base KO\n");
; 		return 0;
; 	}
	
; 	str = trim_whitespaces(str);
; 	sign = set_sign(&str);
; 	absolute_value = get_absolute_value(str, base);
; 	return sign * absolute_value;
; }

; static _check_base_update_ascii(int flag_value, char *present_char)
; {
; 	char forbidden_char[] = "+- \f\n\r\t\v";
; 	for (int i =0; i < 8; ++i)
; 		present_char[forbidden_char[i]] = flag_value;
; }

; int check_base(char *base)
; {
; 	char present_char[128] = {0};

; 	_check_base_update_ascii(1, present_char);
; 	int i = 0;
; 	while (i < 128 && base[i])
; 	{
; 		if (present_char[base[i]] == 1)
; 			return 1;
; 		present_char[base[i]] = 1;
; 		++i;
; 	}
; 	_check_base_update_ascii(0, present_char);
; 	if (i <= 1 || i == 128)
; 		return 1;
; 	return 0;
; }

; void trim_init_present_char(char *present_char)
; {
; 	char whitespace_char[] = " \f\n\r\t\v";

; 	for (int i =0; i < 6; ++i)
; 		present_char[whitespace_char[i]] = 1;
; }

; char *trim_whitespaces(char *str)
; {
; 	char present_char[128] = {};

; 	trim_init_present_char(present_char);
; 	while (*str && present_char[*str] == 1)
; 		++str;
; 	return str;
; }

; int set_sign(char **str)
; {
; 	int sign_neg;

; 	sign_neg = 0;
; 	while (**str && (**str == '-' || **str == '+'))
; 	{
; 		if (**str == '-')
; 			sign_neg ^= 1;
; 		++(*str);
; 	}
; 	if (sign_neg)
; 		return -1;
; 	return 1;
; }

; unsigned int get_absolute_value(char *str, char *base)
; {
; 	int 	abs_val;
; 	char 	char_value[128] = {};
; 	int		len_base;
; 	int 	i;

; 	//clear char_value
; 	for (int i = 0; i < 128; ++i)
; 	char_value[i] = -1;
; 	// set values of the base's chars in char_value
; 	i = 0;
; 	while (base[i])
; 	{
; 		char_value[base[i]] = i;
; 		++i;
; 	}
; 	len_base = i;

; 	// calculate str value
; 	abs_val = 0;
; 	while (*str)
; 	{
; 		if (char_value[*str] == -1)
; 			break;
; 		abs_val = abs_val * len_base + char_value[*str];
; 		++str;
; 	}

; 	return abs_val;
; }
