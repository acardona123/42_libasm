#include "test_mandatory.h"

static int	_test_strdup_null_ptr();
static int	_test_strdup_empty_str();
static int	_test_random_str(int number_of_tests);


void test_strdup()
{
	int	number_of_random_str_tested = 100;
	int	error_cpt;

	printf("=== Tests of ft_strdup ===\n\n");

	error_cpt = 0;
	error_cpt += _test_strdup_empty_str();
	error_cpt += _test_random_str(number_of_random_str_tested);

	printf("\nResults: %d error(s)\n", error_cpt);
	printf("--- End ---\n\n\n");
}

static int	_test_strdup_empty_str()
{
	char	empty;
	char	*dup;

	printf("- Test empty string:\n");
	empty = 0;
	dup = ft_strdup(&empty);
	if (!dup)
	{
		printf("==> Warning (KO?): malloc of size 1 failed ?\n");
		return 0;
	}
	if (*dup)
	{
		printf("==> KO: not empty str\n");
		free(dup);
		return 1;
	}
	free(dup);
	printf("==> OK\n");
	return 0;
}


static int _test_one_random_str();

static int _test_random_str(int number_of_tests)
{
	int	error;

	printf("- Test on %d random string (size max = 1024):\n", number_of_tests);
	error = 0;
	for (int i = 0; i < number_of_tests; ++i)
		error += _test_one_random_str();
	if (!error)
		printf("==> OK\n");
	else
		printf("==> KO: %d / %d errors in the multiple random string test\n", error, number_of_tests);
	return error;
}


static void	_generate_random_str(char *dst);

static int _test_one_random_str()
{
	char	str_ref[1024];
	char	*str_dup;
	int		error;

	_generate_random_str(str_ref);
	error = 0;
	str_dup = ft_strdup(str_ref);
	if (!str_dup)
	{
		printf(" Warning: malloc (size: %ld) fail during the test of a random string duplication. Single test aborted\n", strlen(str_ref));
		return 0;
	}
	if (strcmp(str_ref, str_dup))
	{
		printf(" Test KO:\n  - src: \"%s\"\n  -res: \"%s\"\n", str_ref, str_dup);
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