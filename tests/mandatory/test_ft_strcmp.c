#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/libasm.h"

static int cmp_strcmp_ftstrcmp(const char *str1, const char *str2);

void test_strcmp()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strcmp ===\n");
	error_cpt += cmp_strcmp_ftstrcmp("", "");
	error_cpt += cmp_strcmp_ftstrcmp("000", "001");
	error_cpt += cmp_strcmp_ftstrcmp("123", "122");
	error_cpt += cmp_strcmp_ftstrcmp("Hello", "He__o");
	error_cpt += cmp_strcmp_ftstrcmp("test\t", "test\t1");

	printf("\nResults: %d error(s)\n", error_cpt);

	printf("--- End ---\n\n");
}

static int cmp_strcmp_ftstrcmp(const char *str1, const char *str2)
{
	int	rtn_ref;
	int	rtn_tested;

	rtn_ref = strcmp(str1, str2);
	rtn_tested = ft_strcmp(str1, str2);
	printf ("%d <> %d for \"%s\" vs \"%s\"\n", rtn_ref, rtn_tested, str1, str2);
	return rtn_ref != rtn_tested;
}
