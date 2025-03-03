#include "test_mandatory.h"

static int cmp_strcmp_ftstrcmp(const char *str1, const char *str2);

int test_strcmp()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strcmp ===\n\n");
	error_cpt += cmp_strcmp_ftstrcmp("", "");
	error_cpt += cmp_strcmp_ftstrcmp("000", "001");
	error_cpt += cmp_strcmp_ftstrcmp("123", "122");
	error_cpt += cmp_strcmp_ftstrcmp("Hello", "He__o");
	error_cpt += cmp_strcmp_ftstrcmp("test\t", "test\t1");

		printf("\n-----------\nRESULTS: ");
	if (error_cpt)
		printf("Failure : %d error%s\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		printf("Success\n");

	printf("--- End ---\n");
	return error_cpt != 0;
}

static int	_get_sign(int c)
{
	if (c > 0)
		return 1;
	return -1;
}

static int cmp_strcmp_ftstrcmp(const char *str1, const char *str2)
{
	int	rtn_ref;
	int	rtn_tested;

	rtn_ref = strcmp(str1, str2);
	rtn_tested = ft_strcmp(str1, str2);
	printf ("%d <> %d for \"%s\" vs \"%s\"\n", rtn_ref, rtn_tested, str1, str2);
	return _get_sign(rtn_ref) != _get_sign(rtn_tested);
}
