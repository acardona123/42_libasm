section .text

global ft_strcpy

ft_strcpy:
	;prologue, useless as no local variable is declared and no function is called
	; push rbp
	; mov rbp, rsp
	;code
	xor rax, rax; used as an index i

.cpy_char:
	movzx	r10, byte [rsi + rax]; s1[i] saved in reg for cmp   /!\ we are manipulating bytes and not int (4bytes) which is the default size. So when manipulating the data we need to specify that => use movzx adds the required zeroes to fill the 64bits register
	mov		[rdi + rax], r10;  cmp s1[i] and s2[i]
	; cmp		r10b, 0; else test if end of string reached
	; je		.return; if so then .return
	test	r10b, r10b;more optimized version the cmp 0 because we only want to know if they are different, not >= or <=
	jz		.return
	inc		rax; inc i
	jmp		.cpy_char

.return:
	mov rax, rdi
	;epilogue
	; pop rbp
	ret




;; ===============================================


;alternative methods from the internet:

; Method 1 : using the string manipulation instructions provided by the assembly language
;;			This method is cleaner using implicit pointer increment

; ft_strcpy:
;     mov r10, rdi		; Save destination pointer to return it
; 	cld					;clear the direction flag DF (so the operations on the string [like CMPSB, CMPSD, CMPSQ, CMPSW, LODSB, LODSD, LODSQ,...] increase the index register)
; .cpy_char:
;     lodsb				; Load byte from source (rsi) to AL, increment rsi
;     stosb				; Store byte from AL to dest (rdi), increment rdi
;     test al, al			; Check if null terminator
;     jnz .cpy_char
; 	mov rax, r10
;     ret


; Method 2: using the processor optimization when repeating the same op many times
;;			This method scans the string to calculate its length and the copy it entirely with the rep instruction
;;			

; ft_strcpy:
;     mov     rdx, rdi       ; Save destination pointer for return
;     cld                    ; Clear direction flag (ensure forward copy)

; .find_null:
;     mov     cl, byte [rsi] ; Load byte from source string (CL is the lower byte of CX, the counter reg)
;     inc     rsi            ; Advance source pointer
;     test    cl, cl         ; Check for null terminator
;     jnz     .find_null     ; Continue until null terminator is found

;     sub     rsi, rdx       ; Get length of the string (including null terminator)
;     mov     rcx, rsi       ; Store the length in RCX for rep movsb
;     mov     rsi, rdx       ; Restore the original source pointer

;     rep     movsb          ; Copy the string including null terminator, reproducing movsb as many times as rcx indicates

;     mov     rax, rdx      ; Return destination pointer
;     ret