#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/libasm.h"

static int cmp_strlen_ftstrlen(const char *str);

void test_strlen()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strlen ===\n");
	error_cpt += cmp_strlen_ftstrlen("");
	error_cpt += cmp_strlen_ftstrlen("123456789");
	error_cpt += cmp_strlen_ftstrlen("with a tab \t ...");
	error_cpt += cmp_strlen_ftstrlen("Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
	error_cpt += cmp_strlen_ftstrlen("bgjeogijegivj;kvmdiorgergeggfgfdgt5afavcvx");

	printf("\nResults: %d error(s)\n", error_cpt);

	printf("--- End ---\n\n");
}

static int cmp_strlen_ftstrlen(const char *str)
{
	size_t	rtn_ref;
	size_t	rtn_tested;

	rtn_ref = strlen(str);
	rtn_tested = ft_strlen(str);
	printf ("%zu <> %zu for \"%s\"\n", rtn_ref, rtn_tested, str);
	return rtn_ref != rtn_tested;
}
