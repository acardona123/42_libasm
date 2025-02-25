
;sort the list content in crescent order
;void ft_list_sort(t_list **begin_list, int (*cmp)());
; with cmp used like this in c:
;			(*cmp)(list_ptr->data, other_list_ptr->data);

section .text

	global ft_list_sort
	extern ft_list_size
	extern _ft_list_sort_recursive
	extern _split_list
	extern _merge_lists

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
		sub		rsp, 8				;for helping stack alignment, after the 3 pushs the stack will be aligned
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



; ========================================================================================
;										Equivalent c code
; ========================================================================================


; // void ft_list_sort(t_list **begin_list, int (*cmp)())
; // {
; // 	_ft_list_sort_recursive(begin_list, ft_list_size(*begin_list), cmp);
; // }


; // 	void _ft_list_sort_recursive(t_list **begin_list, int list_size, int (*cmp)())
; // {
; // 	t_list	*head_left;
; // 	t_list	*head_right;

; // 	if ( !begin_list || list_size <= 1)
; // 		return;
; // 	_split_list(*begin_list, list_size, &head_left, &head_right);
; // 	_ft_list_sort_recursive(&head_left, list_size / 2, cmp);
; // 	_ft_list_sort_recursive(&head_right, list_size - list_size / 2, cmp);
; // 	*begin_list = _merge_lists(head_left, head_right, cmp);
; // }


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
; 	int		id;

; 	id_middle_lst = list_size / 2 - 1;

; 	elem = begin_list;
; 	for (int i = 0; i < id_middle_lst; ++i)
; 		elem = elem->next;
; 	return elem;
; }


; // ==== merge elem ====


; void	_pop_src_first_to_dst_back(t_list **last_dest, t_list **head_src)
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
; 		_pop_src_first_to_dst_back(sorted_list_last, head_right);
; 	else if (!*head_right)
; 		_pop_src_first_to_dst_back(sorted_list_last, head_left);
; 	else if (cmp((*head_left)->data, (*head_right)->data) < 0)
; 		_pop_src_first_to_dst_back(sorted_list_last, head_left);
; 	else
; 		_pop_src_first_to_dst_back(sorted_list_last, head_right);
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
