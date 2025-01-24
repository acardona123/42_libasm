#include <stdio.h>

size_t	ft_strlen(const char *s);
int		ft_strcmp(char *dest, const char *src);
// char	*strcpy(char *dest, const char *src);

int main()
{
	char	str1[] = "00";
	char	str2[] = "03";
	int 	value;

	value = ft_strlen(str1);
	printf("len: %d\n\n", value);

	value = ft_strcmp(str1, str1);
	printf("cmp = :%d\n", value);

	value = ft_strcmp(str1, str2);
	printf("cmp < :%d\n", value);

	value = ft_strcmp(str2, str1);
	printf("cmp > :%d\n", value);

	return 0;
}