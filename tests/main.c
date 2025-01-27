#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
ssize_t	ft_write(int fd, const void *buf, size_t count);


static void _test_strlen();
static void _test_strcmp();
static void _test_strcpy();
static void _test_write();

int main()
{
	_test_strlen();
	_test_strcmp();
	_test_strcpy();
	_test_write();

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



int cmp_file_content(const char *file_name, const char *str_ref);

static void _test_write()
{
	int 	fd;
	char	file_name[] = "test_to_dell.txt";
	char	str[] = "This is a test\n";
	int		res_ref;
	int 	errno_ref;
	int 	my_res;
	int		my_errno;

	printf("=== Tests of ft_write ===\n");

	printf("Test on stdout:\n");
	errno = 0;
	my_res = ft_write(1, "Coucou\n", 7);
	my_errno = errno;
	printf("res = %d and errno = %d\n", my_res, my_errno);
	if (my_errno)
		printf("Error: %s\n", strerror(my_errno));

	errno = 0;
	fd = open(file_name,  O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		printf("Test error, can't create test_to_dell.txt\n");
	else
	{
		printf("\nTest on valid file:\n");
		res_ref = strlen(str);
		errno_ref = 0;
		my_res = ft_write(fd, str, (int) strlen(str));
		my_errno = errno;
		printf(" res:%d, errno = %d\n", my_res, my_errno);
		close(fd);
		if (my_res != res_ref || my_errno != errno_ref)
			printf("ko: expected res = %d, errno = %d\n", res_ref, errno_ref);
		else if (!cmp_file_content(file_name, str))
			printf("ok\n");

		printf("\nTest on RONLY file:\n");
		fd = open(file_name, O_RDONLY);
		errno = 0;
		res_ref = write(fd, str, (int) strlen(str)); //wrong open, no rights
		errno_ref = errno;
		errno = 0;
		my_res = ft_write(fd, str, (int) strlen(str)); //wrong open, no rights
		my_errno = errno;
		printf(" res:%d, errno = %d\n", my_res, my_errno);
		close(fd);
		if (my_res != res_ref || my_errno != errno_ref)
			printf("ko: expected res = %d, errno = %d\n", res_ref, errno_ref);
		else if (!cmp_file_content(file_name, str))
			printf("ok\n");
		remove(file_name);
	}

	printf("--- End ---\n\n");
}

int cmp_file_content(const char *file_name, const char *str_ref)
{
	char	read_buff[1024];
	int		fd;

	bzero(read_buff, 1024);
	fd = open(file_name, O_RDONLY);
	read(fd, read_buff, 1024);
	close(fd);
	if (strcmp(str_ref, read_buff))
	{
		printf("ko: wrong copy (wrote \"%s\" instead of %s)\n", read_buff, str_ref);
		return 1;
	}
	return 0;
}