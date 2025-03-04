#include "test_mandatory.h"

typedef int (*test_function)( void );

int main()
{
	logged_printf(true, "===============================================\n");
	logged_printf(true, "        LIBASM MANDATOY FUNCTIONS TEST         \n");
	logged_printf(true, "===============================================\n\n");

	test_function functions_to_test[] = {
		test_strlen,
		test_strcmp,
		test_strcpy,
		test_write,
		test_read_automatic,
		test_strdup,
		NULL};
	int	failed_functions_cpt;
	int	fct_index;

	failed_functions_cpt = 0;
	fct_index = 0;
	while(functions_to_test[fct_index])
	{
		failed_functions_cpt += (*functions_to_test[fct_index++])();
		printf ("_______________________________________________\n\n");
	}

	logged_printf(true, "==== MANDATORY TESTS RESULTS ====\n\n");
	if (!failed_functions_cpt)
		logged_printf(true, "Success ! Congratulations !!!\n\n");
	else
		logged_printf(true, "Failure on %d / %d function%s.\n\n", failed_functions_cpt, fct_index, failed_functions_cpt > 1 ? "s":"");

	return 0;
}
