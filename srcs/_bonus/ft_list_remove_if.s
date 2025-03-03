; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
;	 erase all the elements of the list which data compared to data_ref with cmp gives 0. The removed data will bee freed using free_fct.
;		functions will be called like this in c:
;			(*cmp)(list_ptr->data, data_ref);
;			(*free_fct)(list_ptr->data);

section .text
	global ft_list_remove_if

ft_list_remove_if:
	;prologue: save callee-saved reg (because used in this function)
	push	rbp
	mov		rbp, rsp
	push	r12
	push	r13
	push	r14
	push	r15

	cmp		rdi, byte 0
	je		.return

	;== registers that will be preserved through sub-functions calls (callee-saved) == 
	; mov r12, rdi; begin_list could be stored in reg but less used than elem ==> I prefer to push it and keep the register for elem
	mov		r12, [rdi] 	; elem
	mov		r13, rsi; data_ref
	mov		r14, rdx; cmp
	mov		r15, rcx; free_fct

	;== registers that will have to be pushed onto the stack during the subfunctions calls (caller-saved)
	push	rdi			; begin_list
	mov		rdx, 0		; previous
	push	rdx

	cmp	r12, byte 0
	je	.return
	.loop:
		;if ((*cmp)(elem->data, data_ref) == 0)
		mov		rdi, [r12]
		mov		rsi, r13
		call	r14
		cmp		rax, 0
		je		.remove_element
	.set_next:
		pop		rdx ;just to remove the old previous from stack, could be anywhere
		push	r12 ;update previous
		mov		r12, [r12 + 8]		;elem = elem->next
		cmp		r12, byte 0
		jne		.loop

	.return:
		;epilogue
		pop		rdx ;could be toward any reg
		pop		rdi	;could be toward any reg
		pop		r15
		pop		r14
		pop		r13
		pop		r12
		pop		rbp
		ret

	.remove_element:
		; call (*free_fct)(elem->data)
		mov		rdi, [r12]
		call	r15
		;if (previous == null)
		pop		rdx ;get previous back from stack
		cmp		rdx, byte 0
		je		.update_begin
		.update_previous:
			mov		rcx, [r12 + 8]	; previous->next = elem->next;
			mov		[rdx + 8], rcx	; previous->next = elem->next;
			jmp		.continue_loop
		.update_begin:
			pop		rdi				;get begin_list back from stack
			mov		rcx, [r12 + 8]	; *begin_list = elem->next;
			mov		[rdi], rcx		; *begin_list = elem->next;
			push	rdi
		.continue_loop:
			push	rdx
			jmp		.set_next
