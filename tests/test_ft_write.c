#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

ssize_t	ft_write(int fd, const void *buf, size_t count);

static int cmp_file_content(const char *file_name, const char *str_ref);

void test_write()
{
	int 	fd;
	char	file_name[] = "test_to_dell.txt";
	char	str[] = "This is a test\n";
	int		res_ref;
	int 	errno_ref;
	int 	my_res;
	int		my_errno;
	int 	error_cpt;

	printf("=== Tests of ft_write ===\n");

	error_cpt = 0;

	printf("Test on stdout:\n");
	errno = 0;
	my_res = ft_write(1, "Coucou\n", 7);
	my_errno = errno;
	printf("res = %d and errno = %d\n", my_res, my_errno);
	if (my_errno)
	{
		printf("Error: %s\n", strerror(my_errno));
		++error_cpt;
	}

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
		{
			printf("ko: expected res = %d, errno = %d\n", res_ref, errno_ref);
			++error_cpt;
		}
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
		{
			printf("ko: expected res = %d, errno = %d\n", res_ref, errno_ref);
			++error_cpt;
		}
		else
		{
			if (!cmp_file_content(file_name, str))
				printf("ok\n");
			else
				++error_cpt;
		}
		remove(file_name);
	}

	printf("\nResults: %d error(s)\n", error_cpt);
	printf("--- End ---\n\n");
}

static int cmp_file_content(const char *file_name, const char *str_ref)
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