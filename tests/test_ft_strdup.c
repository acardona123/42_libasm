#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s);

void test_strdup()
{
	printf("=== Tests of ft_strdup ===\n");

	char *dst;
	char src[1204] = "abc";
	// char src[1204] = "test de strdup";

	dst = strdup(src);
	printf("dst = {%s}\n", dst);
	// free(dst);//not commented to check valgrind

	printf("--- End ---\n\n");
}
