#include "test_mandatory.h"

static int	cmp_strcpy_ftstrcpy(const char *src);
static int test_strcpy_overflow();

int test_strcpy()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strcpy ===\n\n");
	error_cpt += cmp_strcpy_ftstrcpy("");
	error_cpt += cmp_strcpy_ftstrcpy("000");
	error_cpt += cmp_strcpy_ftstrcpy("000\ttotoooooooooooooooooooo");
	error_cpt += test_strcpy_overflow();

		printf("\n-----------\nRESULTS: ");
	if (error_cpt)
		printf("Failure : %d error%s\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		printf("Success\n");

	printf("--- End ---\n");
	return error_cpt != 0;
}

static int cmp_strcpy_ftstrcpy(const char *src)
{
	char *dst;
	char *rtn;

	int rtn_ok;
	int cpy_ok;

	dst = calloc(1, strlen(src) + 5);

	rtn = ft_strcpy(dst, src);
	rtn_ok = (dst == rtn);
	cpy_ok = (strcmp(dst, src) == 0);

	printf ("Copy of \"%s\": rtn %s and cpy %s\n", src, rtn_ok ? "ok":"KO", cpy_ok ? "ok":"KO");

	free(dst);
	return !rtn_ok || !cpy_ok;
}

static int test_strcpy_overflow()
{
	printf("Test copy overflow after dst:");

	char src[] = "totoooooooooooo";
	char dst[] = "0123456789";
	char dst_ref[] = "0123456789";


	src[4] = 0;
	strcpy(dst_ref, src);
	ft_strcpy(dst, src);
	if (strcmp(dst, dst_ref) != 0 || strcmp(dst + 5, dst_ref + 5))
	{
		printf("\n expected:\n  dest = {%s}\n  dest_next = {%s}\n", dst_ref, dst_ref + 5);
		printf(" obtained\n  dest = {%s}\n  dest_next = {%s}\n", dst, dst + 5);
		printf(" Error, probably copy more than 1 byte at a time\n");
		return 1;
	}
	printf(" ok\n");
	return 0;
}