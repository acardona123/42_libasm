#include "test_mandatory.h"

void test_display_results(int number_of_errors)
{
	logged_printf(true, "\n-----------\nRESULTS: ");
	if (number_of_errors)
		logged_printf(true, "Failure : %d error%s\n", number_of_errors, number_of_errors > 1 ? "s" : "");
	else
		logged_printf(true, "Success\n");
}