#include "test_bonus.h"

static int _test_preexisting_list( int print);
static int _test_empty_list( int print);

int test_list_push_front()
{
	printf("=== Tests of ft_list_push_front ===\n\n");

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

	printf("--- End ---\n\n\n");
	return error_cpt != 0;
}

static int _test_preexisting_list( int print_details)
{
	t_list	*head;
	t_list	old_first;
	t_list	old_second;
	char*	data1 = "first";
	char*	data2 = "second";
	char*	new_data = "Hi there!";
	int		rtn;

	old_first.data = (void*)data1;
	old_first.next = &old_second;
	old_second.data = (void*)data2;
	old_second.next = 0;
	head = &old_first;

	if (print_details)
	{
		printf("Head addr: %p\n", &head);
		test_print_lst(head);
	}
	ft_list_push_front(&head, (void*)new_data);
	rtn = !head || head->data != new_data || head->next != &old_first || head->next->next != old_first.next;
	if (print_details)
	{
		printf("\nShould now start with a new node node which data is %p\n", new_data);
		test_print_lst(head);	
	}
	if (head && head->data == new_data)
		free(head);
	return (rtn);
}


static int _test_empty_list( int print_details)
{
	t_list	**head;
	t_list *first_null = NULL;
	char*	new_data = "Hi there!";
	int rtn;

	head = &first_null;

	if (print_details)
	{
		printf("Head addr: %p\nNo list", head);
	}
	ft_list_push_front(head, (void*)new_data);
	rtn = (!(*head) || (*head)->data != new_data || (*head)->next != NULL);
	if (print_details)
	{
		printf("\nShould now start with a new node node which data is %p\n", new_data);
		test_print_lst(*head);	
	}
	if (*head)
		free(*head);
	return rtn;
}
