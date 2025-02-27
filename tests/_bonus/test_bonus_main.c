#include "test_bonus.h"

typedef int (*test_function)( void );

int main()
{
	printf("===============================================\n");
	printf("          LIBASM BONUS FUNCTIONS TEST          \n");
	printf("===============================================\n\n");

	test_function functions_to_test[] = {
		test_list_push_front,
		test_list_size,
		test_list_remove_if,
		test_list_sort,
		test_atoi_base,
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

	printf("==== BONUS TESTS RESULTS ====\n\n");
	if (!failed_functions_cpt)
		printf("Success ! Congratulations !!!\n\n");
	else
		printf("Failure on %d / %d function%s.\n\n", failed_functions_cpt, fct_index, failed_functions_cpt > 1 ? "s":"");

	return 0;
}
