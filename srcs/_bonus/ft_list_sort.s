
;sort the list content in crescent order
;void ft_list_sort(t_list **begin_list, int (*cmp)());
; with cmp used like this in c:
;			(*cmp)(list_ptr->data, other_list_ptr->data);

section .text

	global ft_list_sort

ft_list_sort:
