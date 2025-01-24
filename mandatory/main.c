#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);


static void _test_strlen();
static void _test_strcmp();
static void _test_strcpy();

int main()
{
	_test_strlen();
	_test_strcmp();
	_test_strcpy();

	return 0;
}



int cmp_strlen_ftstrlen(const char *str);

static void _test_strlen()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strlen ===\n");
	error_cpt += cmp_strlen_ftstrlen("");
	error_cpt += cmp_strlen_ftstrlen("123456789");
	error_cpt += cmp_strlen_ftstrlen("with a tab \t ...");
	error_cpt += cmp_strlen_ftstrlen("Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
	error_cpt += cmp_strlen_ftstrlen("bgjeogijegivj;kvmdiorgergeggfgfdgt5afavcvx");

	printf("\nResults: %d error(s)\n\n", error_cpt);

	printf("--- End ---\n\n");
}

int cmp_strlen_ftstrlen(const char *str)
{
	size_t	rtn_ref;
	size_t	rtn_tested;

	rtn_ref = strlen(str);
	rtn_tested = ft_strlen(str);
	printf ("%zu <> %zu for \"%s\"\n", rtn_ref, rtn_tested, str);
	return rtn_ref != rtn_tested;
}




int cmp_strcmp_ftstrcmp(const char *str1, const char *str2);

static void _test_strcmp()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strcmp ===\n");
	error_cpt += cmp_strcmp_ftstrcmp("", "");
	error_cpt += cmp_strcmp_ftstrcmp("000", "001");
	error_cpt += cmp_strcmp_ftstrcmp("123", "122");
	error_cpt += cmp_strcmp_ftstrcmp("Hello", "He__o");
	error_cpt += cmp_strcmp_ftstrcmp("test\t", "test\t1");

	printf("\nResults: %d error(s)\n\n", error_cpt);

	printf("--- End ---\n\n");
}

int cmp_strcmp_ftstrcmp(const char *str1, const char *str2)
{
	int	rtn_ref;
	int	rtn_tested;

	rtn_ref = strcmp(str1, str2);
	rtn_tested = ft_strcmp(str1, str2);
	printf ("%d <> %d for \"%s\" vs \"%s\"\n", rtn_ref, rtn_tested, str1, str2);
	return rtn_ref != rtn_tested;
}




int cmp_strcpy_ftstrcpy(const char *src);

static void _test_strcpy()
{
	int error_cpt = 0;

	printf("=== Tests of ft_strcpy ===\n");
	error_cpt += cmp_strcpy_ftstrcpy("");
	error_cpt += cmp_strcpy_ftstrcpy("000");
	error_cpt += cmp_strcpy_ftstrcpy("000\ttotoooooooooooooooooooo");

	printf("\nResults: %d error(s)\n\n", error_cpt);

	printf("--- End ---\n\n");
}

int cmp_strcpy_ftstrcpy(const char *src)
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