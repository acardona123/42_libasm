#include "test_mandatory.h"


static int cmp_strlen_ftstrlen(const char *str);

int test_strlen()
{
	int error_cpt = 0;

	logged_printf(true, "=== Tests of ft_strlen ===\n\n");
	error_cpt += cmp_strlen_ftstrlen("");
	error_cpt += cmp_strlen_ftstrlen("123456789");
	error_cpt += cmp_strlen_ftstrlen("with a tab \t ...");
	error_cpt += cmp_strlen_ftstrlen("Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
	error_cpt += cmp_strlen_ftstrlen("bgjeogijegivj;kvmdiorgergeggfgfdgt5afavcvx");

	test_display_results(error_cpt);
	logged_printf(true, "--- End ---\n");
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
