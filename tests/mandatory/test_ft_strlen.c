#include "test_mandatory.h"


static int cmp_strlen_ftstrlen(const char *str);

int test_strlen()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strlen ===\n\n");
	error_cpt += cmp_strlen_ftstrlen("");
	error_cpt += cmp_strlen_ftstrlen("123456789");
	error_cpt += cmp_strlen_ftstrlen("with a tab \t ...");
	error_cpt += cmp_strlen_ftstrlen("Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
	error_cpt += cmp_strlen_ftstrlen("bgjeogijegivj;kvmdiorgergeggfgfdgt5afavcvx");

		printf("\n-----------\nRESULTS: ");
	if (error_cpt)
		printf("Failure : %d error%s\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		printf("Success\n");
	printf("--- End ---\n");
	return error_cpt != 0;
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
