#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(const char *s);

char	*ft_strcpy(char *dest, const char *src);

static int cmp_strcpy_ftstrcpy(const char *src);

void test_strcpy()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strcpy ===\n");
	error_cpt += cmp_strcpy_ftstrcpy("");
	error_cpt += cmp_strcpy_ftstrcpy("000");
	error_cpt += cmp_strcpy_ftstrcpy("000\ttotoooooooooooooooooooo");

	printf("\nResults: %d error(s)\n\n", error_cpt);

	printf("--- End ---\n\n");
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

