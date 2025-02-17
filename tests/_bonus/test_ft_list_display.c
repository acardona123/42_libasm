#include "test_bonus.h"

static void _print_lst_elem_ptr(t_list *lst)
{
	printf("%p:\n  -data: %p\n  -next: %p\n", lst, lst->data, lst->next);
}

static void _print_lst_elem_str(t_list *lst)
{
	printf("%p:\n  -data: \"%s\"\n  -next: %p\n", lst, (char*)lst->data, lst->next);
}

static void _print_lst_elem_int(t_list *lst)
{
	printf("%p:\n  -data: %d\n  -next: %p\n", lst, *(int *)lst->data, lst->next);
}

static void _print_lst_elem_int_silent(t_list *lst)
{
	printf("%d", *(int *)lst->data);
}

static void _test_print_lst_typed(t_list *lst_head, void (*print_lst_elem)(t_list *lst))
{
	t_list *elem;

	printf("--List--\nStart at %p\n", lst_head);
	elem = lst_head;
	while (elem)
	{
		(*print_lst_elem)(elem);
		elem = elem->next;
	}
	printf("--End list--\n");
}


static void _test_print_lst_typed_silent(t_list *lst_head, void (*print_lst_elem)(t_list *lst))
{
	t_list *elem;

	printf("[");
	elem = lst_head;
	while (elem)
	{
		(*print_lst_elem)(elem);
		elem = elem->next;
		printf("%s", elem ? ", " : "");
	}
	printf("]\n");
}

void test_print_lst(t_list *lst_head)
{
	_test_print_lst_typed(lst_head, _print_lst_elem_ptr);
}

void test_print_lst_str(t_list *lst_head)
{
	_test_print_lst_typed(lst_head, _print_lst_elem_str);
}

void test_print_lst_int(t_list *lst_head)
{
	_test_print_lst_typed(lst_head, _print_lst_elem_int);
}

void test_print_lst_int_silent(t_list *lst_head)
{
	_test_print_lst_typed_silent(lst_head, _print_lst_elem_int_silent);
}