#include "test_bonus.h"

typedef int (*test_function)( void );

int main()
{
	int	failed_functions_cpt;
	int	fct_index;
	test_function functions_to_test[] = {
		test_list_push_front,
		test_list_size,
		test_list_remove_if,
		test_list_sort,
		test_atoi_base,
		NULL};

	open_log_file("test_bonus.log");

	logged_printf(true, "===============================================\n");
	logged_printf(true, "          LIBASM BONUS FUNCTIONS TEST          \n");
	logged_printf(true, "===============================================\n\n");

	failed_functions_cpt = 0;
	fct_index = 0;
	while(functions_to_test[fct_index])
	{
		failed_functions_cpt += (*functions_to_test[fct_index++])();
		logged_printf(true, "_______________________________________________\n\n");
	}

	logged_printf(true, "==== BONUS TESTS RESULTS ====\n\n");
	if (!failed_functions_cpt)
		logged_printf(true, "Success ! Congratulations !!!\n\n");
	else
		logged_printf(true, "Failure on %d / %d function%s.\n\n", failed_functions_cpt, fct_index, failed_functions_cpt > 1 ? "s":"");

	close_log_file();
	return 0;
}
