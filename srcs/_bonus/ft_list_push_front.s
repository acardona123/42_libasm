; void ft_list_push_front(t_list **begin_list, void *data)

section .text

	global ft_list_push_front
	extern malloc

ft_list_push_front:
	; prologue
	push rbp
	mov rbp, rsp

;create list elem
	;save params that will be modified by malloc in caller-saved registers (). 3 options to do so:
	; - knowing wich registers are gonna impaceted by malloc and therefore stroring the data in another one, whichever it is.
	;	-> not a good idea as it is dependent to the malloc implementation
	; - saving the data into the stack
	;   ->easily understood and can be done for as many registers as necessary. But relatively slow compare to saving them in registers
	; - saving them in callee-saved registers: r12-r15
	;	-> most performance but limited amount of data saved

	push rdi; save begin_list in stack
	push rsi; save data in stack

.new_elem: ;malloc new elem
	mov rdi, 16; set malloc size for t_list (2 ptr = 2*8o)
	;check stack: ok because when called: 0[16], then push return => -8[16], then push rbp=>(-8-8)[16] = 0[16], then push rdi and push rsi=> 0-8-8[16]=0[16]
	call QWORD [rel malloc wrt ..got]
	cmp rax, 0 ;check for malloc fail
	je .return
.set_elem_content:
	pop rsi			 	;get back data
	pop rdi				;get back begin_list
	mov [rax], rsi		; set new_elem.data
	mov r9, [rdi]		;get *begin_list, first elem addr
	mov [rax + 8], r9	;set new_elem.next = *begin_list
.insert_elem:
	mov [rdi], rax
.return:
	; epilogue
	pop rbp;
	ret;

