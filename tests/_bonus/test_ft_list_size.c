#include "test_bonus.h"

int test_list_size()
{
	logged_printf(true, "=== Tests of ft_list_size ===\n\n");
	int error_cpt = 0;

	//build list
	t_list	first;
	t_list	second;
	char*	data1 = "first";
	char*	data2 = "second";
	char*	new_data = "Hi there!";

	first.data = (void*)data1;
	first.next = &second;
	second.data = (void*)data2;
	second.next = 0;

	//tests len:
	int len;
	int expected_len;

	len = ft_list_size(&first);
	expected_len = 2;
	logged_printf(true, "- len : %d vs %d -> %s\n", len, expected_len, len ==  expected_len ? "OK" : "KO");
	error_cpt += len !=  expected_len;

	len = ft_list_size(&second);
	expected_len = 1;
	logged_printf(true, "- len : %d vs %d -> %s\n", len, expected_len, len ==  expected_len ? "OK" : "KO");
	error_cpt += len !=  expected_len;

	len = ft_list_size((t_list*) NULL);
	expected_len = 0;
	logged_printf(true, "- len : %d vs %d -> %s\n", len, expected_len, len ==  expected_len ? "OK" : "KO");
	error_cpt += len !=  expected_len;

	test_display_results(error_cpt);
	logged_printf(true, "--- End ---\n");
	return error_cpt != 0;
}
