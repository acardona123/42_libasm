
;sort the list content in crescent order
;void ft_list_sort(t_list **begin_list, int (*cmp)());
; with cmp used like this in c:
;			(*cmp)(list_ptr->data, other_list_ptr->data);

section .text

	global ft_list_sort
	extern ft_list_size

ft_list_sort:
	.ft_list_sort_prologue:
		push	rbp
		mov		rbp, rsp
		push	rdi			;caller save of  begin_list
		push	rsi			;caller save of  cmp
	.ft_list_sort_null_list:
		cmp		rdi, 0
		je		.ft_list_sort_ret
	.ft_list_sort_get_size:
		mov		rdi, [rdi]
		call	ft_list_size
	.ft_list_sort_merge_sort:
		pop		rdx			;arg1 = retrieve cmp
		mov		rsi, rax	;arg2 = list_size
		pop		rdi			;arg3 = retrieve begin_list
		call	_ft_list_sort_recursive
	.ft_list_sort_ret:
		.ft_list_sort_epilogue:
			mov	rsp, rbp
			pop	rbp
		ret


; void _ft_list_sort_recursive(t_list **begin_list, int list_size, int (*cmp)())
_ft_list_sort_recursive:
	.recursion_prologue:
		push 	rbp
		mov 	rbp, rsp
		sub		rsp, 8				;for helping stack alignment, after the 3 pushes the stack will be aligned
		push	r12
		push	r13
		push	r14
	.recursion_variable_declaration:
		mov		r12, rdi			;save begin_list
		mov		r13, rsi			;save list_size
		mov		r14, rdx			;save cmp
		sub 	rsp, 16				;memory allocation for t_list *head_left and t_list	*head_right;
		mov		qword [rsp], 0		;init head_left to NULL
		mov		qword [rsp + 8], 0	;init head_write to NULL
	.recursion_end_check:
		cmp		r13, 1
		jle		.recursion_ret
	.recursion_split_list:
		mov		rdi, [r12]		;arg1 = *begin_list
		mov		rsi, r13		;arg2 = list_size
		mov		rdx, rsp		;arg3 = &head_left
		mov		rcx, rsp	
		add		rcx, 8			;arg4 = &head_right
		call	_split_list
	.recursion_sort_first_half:
		.get_first_half_size:	;list_size / 2
			mov		rax, r13
			xor		rdx, rdx
			mov		rdi, 2
			div		rdi
		mov		rdi, rsp		;arg1 &head_left
		mov		rsi, rax		;arg2 list_size / 2
		mov		rdx, r14		;arg3 cmp
		call	_ft_list_sort_recursive
	.recursion_sort_second_half:
		.get_second_half_size:	;list_size - list_size / 2
			mov		rax, r13
			xor		rdx, rdx
			mov		rsi, 2
			div		rsi
			mov		rsi, r13
			sub		rsi, rax
		mov		rdi, rsp
		add		rdi, 8			;arg1 &head_right
		; mov	rsi, rsi		;arg2 list_size - list_size / 2
		mov		rdx, r14		;arg3 cmp
		call	_ft_list_sort_recursive
	.recursion_merge:
		mov		rdi, [rsp]		;arg1 head_left
		mov		rsi, [rsp + 8]	;arg2 head_right
		mov		rdx, r14		;arg3 cmp
		call	_merge_lists
		mov		[r12], rax
	.recursion_ret:
		.recursion_epilogue:
			add	rsp, 16
			pop	r14
			pop	r13
			pop	r12
			mov	rsp, rbp
			pop	rbp
		ret




; ===== Split list in halves =====

; void _split_list(t_list *begin_list, int list_size, t_list	**head_left, t_list	**head_right)
_split_list:
	.split_list_prologue:
		push	rbp
		mov		rbp, rsp
	mov		[rdx], rdi				; set *head_left = begin_list
	.get_list_middle_elem:			; get the last elem of the first half of the list
		; mov	rdi, rdi			; arg1 = begin_list (already the case)
		; mov	rsi, rsi			; arg2 = list_size (already the case)
		push	rcx
		sub 	rsp, 8				; stack alignment
		call	_get_middle_element
		add		rsp, 8
		pop		rcx
	.split_after_middle_elem:
		add		rax, 8					; get pointer to middle_elem->next
		mov		rdi, [rax]				; get value of middle_elem->next
		mov		[rcx], rdi				; set *head_right = middle_elem->next
		mov		qword [rax], 0			; set middle_elem->next = 0
	.split_list_ret:
		.split_list_epilogue:
			mov		rsp, rbp
			pop		rbp
		ret

; t_list* _get_middle_element(t_list *begin_list, int list_size)
_get_middle_element:
	; .get_mid_elem_prologue:
	; 	push	rbp
	; 	mov		rbp, rsp
	.get_mid_elem_index_calc:
		mov		rax, rsi		; dividend =  list_size
		xor		rdx, rdx		; dividend complement
		mov		r8, 2			; divisor = 2
		div		r8				; list_size / 2
		dec		rax				; list_size / 2 - 1
		mov		rsi, rax		; save i_max = list_size / 2 - 1
	.get_mid_elem_for_loop:
		.get_mid_elem_for_loop_init:
			xor		rcx, rcx						; i = 0
			; mov	rdi, rdi						; t_list *elem = begin_list
		.get_mid_elem_for_loop_routine:
			.get_mid_elem_for_loop_test:
				cmp		rcx, rsi
				jge		.get_mid_elem_ret			; if i >= imax
			.get_mid_elem_for_loop_content:	
				mov		rdi, qword [rdi + 8]		; elem = elem->next
				inc		rcx							; ++i
				jmp		.get_mid_elem_for_loop_routine
	.get_mid_elem_ret:
		; .get_mid_elem_epilogue:
		; 	mov		rsp, rbp
		; 	pop		rbp
		mov		rax, rdi		; return (elem)
		ret






; ===== Merge two sorted lists together =====


; t_list *_merge_lists(t_list *head_left, t_list *head_right, int (*cmp)())
_merge_lists:
	.merge_prologue:
		push	rbp
		mov		rbp, rsp
		push	r12					;callee-saved registers
		push	r13					;callee-saved registers
		push	r14					;callee-saved registers
		push	r15					;callee-saved registers
	.merge_variable_declaration:
		sub		rsp, 32					; mem allocation for those var:
		mov		[rsp], rdi				; save arg1 head_left
		mov		[rsp + 8], rsi			; save arg2 head_right
		mov		qword [rsp + 16], 0		; declaration of sorted_list_head
		mov		qword [rsp + 24], 0		; declaration of sorted_last
	.merge_main_args_save:
		mov		r12, rsp
		add		r12, 24				; &sorted_last
		mov		r13, rsp			; &head_left
		mov		r14, rsp
		add		r14, 8				; &head_right
		mov		r15, rdx			; cmp
	.merge_extract_first_elem_as_head:
		mov		rdi, r12			; arg1 = &sorted_last
		mov		rsi, r13			; arg2 = &head_left
		mov		rdx, r14			; arg3 = &head_right
		mov		rcx, r15			; arg4 = cmp
		; sub	rsp, 0				; stack alignment already done
		call	_merge_one_elem
		mov		rdi, [r12]
		mov		[rsp + 16], rdi		; sorted_list_head = sorted_last
	.merge_extract_all_remaining_elem:
		._merge_while:
			.merge_while_test:				; head_left || head_right
				cmp		qword [rsp], 0
				jne		.merge_while_content
				cmp		qword [rsp + 8], 0
				jne		.merge_while_content
				jmp .merge_ret
			.merge_while_content:
				mov		rdi, r12			; arg1 = &sorted_last
				mov		rsi, r13			; arg2 = &head_left
				mov		rdx, r14			; arg3 = &head_right
				mov		rcx, r15			; arg4 = cmp
				; sub	rsp, 0				; stack alignment already done
				call	_merge_one_elem
				jmp .merge_while_test
	.merge_ret:
		mov		rax, [rsp + 16]				;return sorted_list_head
		.merge_epilogue:
			add		rsp, 32					;free mem
			pop		r15
			pop		r14
			pop		r13
			pop		r12
			mov		rsp, rbp
			pop		rbp
		ret


; void	_merge_one_elem(t_list **sorted_list_last, t_list **head_left, t_list **head_right, int (*cmp)())
_merge_one_elem:
	.merge_one_elem_prologue:
		push	rbp
		mov		rbp, rsp
	.set_args_of_pop_src_first_after_dst:
		.merge_one_test_which_list_to_merge:
			cmp		qword [rsi], 0					; test *head_left vs 0
			je		.merge_one_set_arg_right
			cmp		qword [rdx], 0					; test *head_right vs 0
			je		.merge_one_set_arg_left
			.cmp_lists_heads_data:
				.save_variables_through_call:
					push	r12						; callee-saved regs
					push	r13						; callee-saved regs
					push	r14						; callee-saved regs
					mov		r12, rdi				; save sorted_list_last
					mov		r13, rsi				; save head_left
					mov		r14, rdx				; save head_right
				.set_comp_args:
					mov		rdi, [r13]
					mov		rdi, [rdi]				; arg1 = (*head_left)->data
					mov		rsi, [rdx]
					mov		rsi, [rsi]				; arg2 = (*head_right)->data
				.call_comparison:
					sub		rsp, 8					; stack alignment
					call	rcx					; (*cmp)((*head_left)->data, (*head_right)->data))
					add		rsp, 8
				.restore_saved_regs:
					mov		rdi, r12				; restore sorted_list_last
					mov		rsi, r13				; restore head_left
					mov		rdx, r14				; restore head_right
					pop		r14						; restore callee-saved regs
					pop		r13						; restore callee-saved regs
					pop		r12						; restore callee-saved regs
			
			cmp		eax, 0
			jle		.merge_one_transfer_elem
		.merge_one_set_arg_right:
			mov		rsi, rdx			; arg2 = head_right
			jmp		.merge_one_transfer_elem
		.merge_one_set_arg_left:
			; mov	rsi, rsi			; arg2 = head_left
			jmp		.merge_one_transfer_elem
	.merge_one_transfer_elem:
		; mov	rdi, rdi				; arg1 = sorted_list_last
		; sub	rsp, 0					; stack already aligned
		mov  r8, [rsi]	;test to check which one is pop
		mov r8, [r8]
		call	_pop_src_first_after_dst
	.merge_one_elem_ret:
		._merge_one_elem_epilogue:
			mov		rsp, rbp
			pop		rbp
		ret


; void	_pop_src_first_after_dst(t_list **last_dest, t_list **head_src)
_pop_src_first_after_dst:
	.pop_first_to_dst_prologue:
		push	rbp
		mov		rbp, rsp
	mov		rdx, qword [rdi]				; save *last_dest
	mov		rcx, qword [rsi]				; save *head_src
	.pop_first_to_dst_append_to_dest_elem:
		cmp		rdx, 0
		je		.pop_first_to_dst_update_last_dest
		mov		qword [rdx + 8], rcx		; (*last_dest)->next = *head_src
	.pop_first_to_dst_update_last_dest:
		mov		qword [rdi], rcx			; *last_dest = *head_src
		mov		r8, [rcx + 8]		
		mov		[rsi], r8			; *head_src = (*head_src)->next;
		mov		r8, [rdi]
		mov		qword [r8 + 8], 0
	.pop_first_to_dst_ret:
		.pop_first_to_dst_epilogue:
			mov		rsp, rbp
			pop		rbp
		ret


; ========================================================================================
;								Similar c code
; ========================================================================================


; void ft_list_sort(t_list **begin_list, int (*cmp)())
; {
; 	_ft_list_sort_recursive(begin_list, ft_list_size(*begin_list), cmp);
; }


; void _ft_list_sort_recursive(t_list **begin_list, int list_size, int (*cmp)())
; {
; 	t_list	*head_left;
; 	t_list	*head_right;

; 	if ( !begin_list || list_size <= 1)
; 		return;
; 	_split_list(*begin_list, list_size, &head_left, &head_right);
; 	_ft_list_sort_recursive(&head_left, list_size / 2, cmp);
; 	_ft_list_sort_recursive(&head_right, list_size - list_size / 2, cmp);
; 	*begin_list = _merge_lists(head_left, head_right, cmp);
; }

; // ==== split list ====


; static	t_list* _get_middle_element(t_list *begin_list, int list_size);

; void _split_list(t_list *begin_list, int list_size, t_list	**head_left, t_list	**head_right)
; {
; 	t_list *middle_elem;

; 	middle_elem = _get_middle_element(begin_list, list_size);
; 	*head_left = begin_list;
; 	*head_right = middle_elem->next;
; 	middle_elem->next = 0;
; }

; t_list* _get_middle_element(t_list *begin_list, int list_size)
; {
; 	int 	id_middle_lst;
; 	t_list*	elem;

; 	id_middle_lst = list_size / 2 - 1;

; 	elem = begin_list;
; 	for (int i = 0; i < id_middle_lst; ++i)
; 		elem = elem->next;
; 	return elem;
; }


; // ==== merge elem ====


; void	_pop_src_first_after_dst(t_list **last_dest, t_list **head_src)
; {
; 	if (*last_dest)
; 		(*last_dest)->next = *head_src;
; 	*last_dest = *head_src;
; 	*head_src = (*head_src)->next;
; 	(*last_dest)->next = NULL;
; }

; void	_merge_one_elem(t_list **sorted_list_last, t_list **head_left, t_list **head_right, int (*cmp)())
; {
; 	if (!*head_left)
; 		_pop_src_first_after_dst(sorted_list_last, head_right);
; 	else if (!*head_right)
; 		_pop_src_first_after_dst(sorted_list_last, head_left);
; 	else if (cmp((*head_left)->data, (*head_right)->data) < 0)
; 		_pop_src_first_after_dst(sorted_list_last, head_left);
; 	else
; 		_pop_src_first_after_dst(sorted_list_last, head_right);
; }

; t_list *_merge_lists(t_list *head_left, t_list *head_right, int (*cmp)())
; {
; 	t_list *sorted_list_head;
; 	t_list	*sorted_last;

; 	sorted_list_head = NULL;
; 	_merge_one_elem(&sorted_list_head, &head_left, &head_right, cmp);
; 	sorted_last = sorted_list_head;
; 	while (head_left || head_right)
; 		_merge_one_elem(&sorted_last, &head_left, &head_right, cmp);
; 	return sorted_list_head;
; }