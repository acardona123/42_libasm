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


static int _test_remove_middle_elem( int print_details);
static int _test_remove_first_elem( int print_details);


int test_list_remove_if()
{
	printf("=== Tests of ft_list_list_remove_if ===\n\n");

	int error_cpt = 0;

	printf("- Test delete first element:\n");
	if (_test_remove_first_elem(0))
	{
		printf("KO\n");
		error_cpt += _test_remove_first_elem(1);
	} else {
		printf("ok\n");
	}

	printf("- Test delete middle element:\n");
	if (_test_remove_middle_elem(0))
	{
		printf("KO\n");
		error_cpt += _test_remove_middle_elem(1);
	} else {
		printf("ok\n");
	}	

	printf("\nResults: %d error(s)\n", error_cpt);
	printf("--- End ---\n\n\n");
	return error_cpt != 0;
}

static int _test_remove_middle_elem( int print_details)
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
	{
		printf("Reference data: \"%s\"\n", data_ref);
		printf("Before:\n"); 
		test_print_lst_str(head);
	}
	free_called = 0;
	ft_list_remove_if(&head, data_ref, _cmp, _free_function);
	if (print_details)
	{
		printf("After:\n"); 
		test_print_lst_str(head);
	}
	return (!head || head != &first || head->next != &third || !free_called);
}

static int _test_remove_first_elem( int print_details)
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
	{
		printf("Before:\n"); 
		test_print_lst_str(head);
	}
	free_called = 0;
	ft_list_remove_if(&head, data_ref, _cmp, _free_function);
	if (print_details)
	{
		printf("After:\n");
		test_print_lst_str(head);
		printf("Delete function called: %s\n", free_called != 0 ? "yes" : "no");
	}
	return (!head || head != &second || head->next != &third || !free_called);
}