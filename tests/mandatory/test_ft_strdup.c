#include "test_mandatory.h"

static int	_test_strdup_null_ptr();
static int	_test_strdup_empty_str();
static int	_test_random_str(int number_of_tests);


int test_strdup()
{
	int	number_of_random_str_tested = 100;
	int	error_cpt;

	logged_printf(true, "=== Tests of ft_strdup ===\n\n");

	error_cpt = 0;
	error_cpt += _test_strdup_empty_str();
	error_cpt += _test_random_str(number_of_random_str_tested);

	test_display_results(error_cpt);
	logged_printf(true, "--- End ---\n");
	return error_cpt != 0;
}

static int	_test_strdup_empty_str()
{
	char	empty;
	char	*dup;

	logged_printf(true, "- Test empty string:\n");
	empty = 0;
	dup = ft_strdup(&empty);
	if (!dup)
	{
		logged_printf(true, "==> Warning (KO?): malloc of size 1 failed ?\n");
		return 0;
	}
	if (*dup)
	{
		logged_printf(true, "==> KO: not empty str\n");
		free(dup);
		return 1;
	}
	free(dup);
	logged_printf(true, "==> OK\n");
	return 0;
}


static int _test_one_random_str();

static int _test_random_str(int number_of_tests)
{
	int	error;

	logged_printf(true, "- Test on %d random string (size max = 1024):\n", number_of_tests);
	error = 0;
	for (int i = 0; i < number_of_tests; ++i)
		error += _test_one_random_str();
	if (!error)
		logged_printf(true, "==> OK\n");
	else
		logged_printf(true, "==> KO: %d / %d errors in the multiple random string test\n", error, number_of_tests);
	return error;
}


static void	_generate_random_str(char *dst);

static int _test_one_random_str()
{
	char	str_ref[1024] = {};
	char	*str_dup;
	int		error;

	_generate_random_str(str_ref);
	error = 0;
	str_dup = ft_strdup(str_ref);
	if (!str_dup)
	{
		logged_printf(true, " Warning: malloc (size: %ld) fail during the test of a random string duplication. Single test aborted\n", strlen(str_ref));
		return 0;
	}
	if (strcmp(str_ref, str_dup))
	{
		logged_printf(true, " Test KO:\n  - src: \"%s\"\n  -res: \"%s\"\n", str_ref, str_dup);
		++error;
	}
	free(str_dup);
	return error;	
}

static void	_generate_random_str(char *dst)
{
	int	len;

	srand(time(NULL));
	len = rand() % 1023;
	dst[len + 1] = 0;
	while (len)
		dst[len--] = 1 + rand()%127;
}