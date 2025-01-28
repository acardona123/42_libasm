#include "../../includes/libasm_bonus.h"
#include <stdio.h>

static void _print_lst_elem(t_list *lst);
static void _print_lst(t_list *lst_head);
static int _test_preexisting_list( int print);
static int _test_empty_list( int print);

void test_list_push_front()
{
	printf("=== Tests of ft_list_push_front ===\n");

	int error_cpt = 0;

	printf("- Preexisting list: ");
	if (_test_preexisting_list(0))
	{
		printf("KO\n");
		++error_cpt;
		_test_preexisting_list(1);

	}
	else
		printf("ok\n");

	printf("- Empty list: ");
	if (_test_empty_list(0))
	{
		printf("KO\n");
		++error_cpt;
		_test_empty_list(1);
	}
	else
		printf("ok\n");

	printf("\nResults: %d error(s)\n", error_cpt);

	printf("--- End ---\n\n");
}

static int _test_preexisting_list( int print_details)
{
	t_list	*head;
	t_list	old_first;
	t_list	old_second;
	char*	data1 = "first";
	char*	data2 = "second";
	char*	new_data = "Hi there!";

	old_first.data = (void*)data1;
	old_first.next = &old_second;
	old_second.data = (void*)data2;
	old_second.next = 0;
	head = &old_first;

	if (print_details)
	{
		printf("Head addr: %p\n", &head);
		_print_lst(head);
	}
	ft_list_push_front(&head, (void*)new_data);
	if (print_details)
	{
		printf("\nShould now start with a new node node which data is %p\n", new_data);
		_print_lst(head);	
	}
	return (!head || head->data != new_data || head->next != &old_first || head->next->next != old_first.next);
}


static int _test_empty_list( int print_details)
{
	t_list	**head;
	t_list *first_null;
	char*	new_data = "Hi there!";

	head = &first_null;

	if (print_details)
	{
		printf("Head addr: %p\nNo list", head);
	}
	ft_list_push_front(head, (void*)new_data);
	if (print_details)
	{
		printf("\nShould now start with a new node node which data is %p\n", new_data);
		_print_lst(*head);	
	}
	return (!(*head) || (*head)->data != new_data || (*head)->next != NULL);
}



static void _print_lst_elem(t_list *lst)
{
	printf("%p:\n  -data: %p\n  -next: %p\n", lst, lst->data, lst->next);
} 

static void _print_lst(t_list *lst_head)
{
	t_list *elem;

	printf("List:\nStart at %p\n", lst_head);
	elem = lst_head;
	while (elem)
	{
		_print_lst_elem(elem);
		elem = elem->next;
	}
	printf("--End list--\n");
}