#include "test_bonus.h"

int free_called;

static int	_cmp(void* var1, void* var2)
{
	return (strcmp((char*) var1, (char*) var2));
}

static void _free_function(void *data)
{
	++free_called;
}


static int _test_remove_middle_elem( bool print_details);
static int _test_remove_first_elem( bool print_details);


int test_list_remove_if()
{
	logged_printf(true, "=== Tests of ft_list_list_remove_if ===\n\n");

	int error_cpt = 0;

	error_cpt += test_list_and_display_results("Test delete first element", _test_remove_first_elem);
	error_cpt += test_list_and_display_results("Test delete middle element", _test_remove_middle_elem);

	logged_printf(true, "\n-----------\nRESULTS: ");
	if (error_cpt)
		logged_printf(true, "Failure : %d error%s\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		logged_printf(true, "Success\n");
	logged_printf(true, "--- End ---\n");
	return error_cpt != 0;
}

static int _test_remove_middle_elem(bool print_details)
{
	t_list	*head;
	t_list	first;
	t_list	second;
	t_list	third;
	char*	data1 = "first";
	char*	data2 = "second";
	char*	data3 = "third";
	char*	data_ref = "second";

	head = &first;
	first.data = (void*)data1;
	first.next = &second;
	second.data = (void*)data2;
	second.next = &third;
	third.data = (void*)data3;
	third.next = NULL;

	if (print_details)
		logged_printf(false,  " /!\\ Same test\n");
	
	logged_printf(print_details, "Removed if *data = \"%s\"\n", data_ref);
	logged_printf(print_details, "Before:\n"); 
	test_print_lst_str(print_details, head);
	
	free_called = 0;
	ft_list_remove_if(&head, data_ref, _cmp, _free_function);
	
	logged_printf(print_details, "After:\n"); 
	test_print_lst_str(print_details, head);
	logged_printf(print_details, "Delete function called: %s\n", free_called != 0 ? "yes" : "no");
	
	return (!head || head != &first || head->next != &third || !free_called);
}

static int _test_remove_first_elem(bool print_details)
{
	t_list	*head;
	t_list	first;
	t_list	second;
	t_list	third;
	char*	data1 = "first";
	char*	data2 = "second";
	char*	data3 = "third";
	char*	data_ref = "first";
	int 	res;

	head = &first;
	first.data = (void*)data1;
	first.next = &second;
	second.data = (void*)data2;
	second.next = &third;
	third.data = (void*)data3;
	third.next = NULL;

	if (print_details)
		logged_printf(false,  " /!\\ Same test\n");
	
	logged_printf(print_details, "Removed if *data = \"%s\"\n", data_ref);
	logged_printf(print_details, "Before:\n"); 
	test_print_lst_str(print_details, head);

	free_called = 0;
	ft_list_remove_if(&head, data_ref, _cmp, _free_function);
	
	logged_printf(print_details, "After:\n");
	test_print_lst_str(print_details, head);
	logged_printf(print_details, "Delete function called: %s\n", free_called != 0 ? "yes" : "no");

	return (!head || head != &second || head->next != &third || !free_called);
}