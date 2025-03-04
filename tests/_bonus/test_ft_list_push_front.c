#include "test_bonus.h"

static int _test_preexisting_list( bool print);
static int _test_empty_list( bool print);

int test_list_push_front()
{
	logged_printf(true, "=== Tests of ft_list_push_front ===\n\n");

	int error_cpt = 0;

	error_cpt += test_list_and_display_results("Preexisting list", _test_preexisting_list);
	error_cpt += test_list_and_display_results("Empty list", _test_empty_list);
	
	test_display_results(error_cpt);
	logged_printf(true, "--- End ---\n");
	return error_cpt != 0;
}

static int _test_preexisting_list(bool print_details)
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
		logged_printf(false, " /!\\ Same test\n");

	logged_printf(print_details, "Head stoked at the address %p\nBefore:\n", &head);
	test_print_lst(print_details, head);

	ft_list_push_front(&head, (void*)new_data);
	rtn = !head || head->data != new_data || head->next != &old_first || head->next->next != old_first.next;
	
	logged_printf(print_details, "After:\nShould now start with a new node which data is %p:\n", new_data);
	test_print_lst(print_details, head);
	
	if (head && head->data == new_data)
		free(head);
	return (rtn);
}


static int _test_empty_list( bool print_details)
{
	t_list	**head;
	t_list *first_null = NULL;
	char*	new_data = "Hi there!";
	int rtn;

	head = &first_null;

	if (print_details)
		logged_printf(false, " /!\\ Same test\n");

	logged_printf(print_details, "Head stoked at the address %p\nNo list", head);
	
	ft_list_push_front(head, (void*)new_data);
	rtn = (!(*head) || (*head)->data != new_data || (*head)->next != NULL);
	
	logged_printf(print_details, "\nShould now start with a new node node which data is %p\n", new_data);
	test_print_lst(print_details, *head);	

	if (*head)
		free(*head);
	return rtn;
}
