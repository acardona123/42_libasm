#include "test_bonus.h"

static void _print_lst_elem_ptr(bool print_stdout, t_list *lst)
{
	logged_printf(print_stdout, "%p:\n  -data: %p\n  -next: %p\n", lst, lst->data, lst->next);
}

static void _print_lst_elem_str(bool print_stdout, t_list *lst)
{
	logged_printf(print_stdout, "%p:\n  -data: \"%s\"\n  -next: %p\n", lst, (char*)lst->data, lst->next);
}

static void _print_lst_elem_int(bool print_stdout, t_list *lst)
{
	logged_printf(print_stdout, "%p:\n  -data: %d\n  -next: %p\n", lst, *(int *)lst->data, lst->next);
}

static void _print_lst_elem_int_silent(bool print_stdout, t_list *lst)
{
	logged_printf(print_stdout, "%d", *(int *)lst->data);
}

static void _test_print_lst_typed(bool print_stdout, t_list *lst_head, void (*print_lst_elem)(bool print_stdout, t_list *lst))
{
	t_list *elem;

	logged_printf(print_stdout, "--List--\nStart at %p\n", lst_head);
	elem = lst_head;
	while (elem)
	{
		(*print_lst_elem)(print_stdout, elem);
		elem = elem->next;
	}
	logged_printf(print_stdout, "--End list--\n");
}


static void _test_print_lst_typed_silent(bool print_stdout, t_list *lst_head, void (*print_lst_elem)(bool print_stdout, t_list *lst))
{
	t_list *elem;

	logged_printf(print_stdout, "[");
	elem = lst_head;
	while (elem)
	{
		(*print_lst_elem)(print_stdout, elem);
		elem = elem->next;
		logged_printf(print_stdout, "%s", elem ? ", " : "");
	}
	logged_printf(print_stdout, "]\n");
}

void test_print_lst(bool print_stdout, t_list *lst_head)
{
	_test_print_lst_typed(print_stdout, lst_head, _print_lst_elem_ptr);
}

void test_print_lst_str(bool print_stdout, t_list *lst_head)
{
	_test_print_lst_typed(print_stdout, lst_head, _print_lst_elem_str);
}

void test_print_lst_int(bool print_stdout, t_list *lst_head)
{
	_test_print_lst_typed(print_stdout, lst_head, _print_lst_elem_int);
}

void test_print_lst_int_silent(bool print_stdout, t_list *lst_head)
{
	_test_print_lst_typed_silent(print_stdout, lst_head, _print_lst_elem_int_silent);
}