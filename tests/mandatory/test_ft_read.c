#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../../includes/libasm.h"

void test_read(int test_std_in)
{
	int 	fd;
	char	file_name[] = "test_to_dell.txt";
	char	read_buff[1024];
	char	str_ref[] = "This is a test\n";
	int		res_ref;
	int 	errno_ref;
	int 	my_res;
	int		my_errno;

	int	error_cpt = 0;

	printf("=== Tests of ft_read ===\n");

	if (test_std_in)
	{
		printf("Test on stdin, write anything (less than 1024 char) and check if the printed text is equal to it:\n");
		errno = 0;
		my_res = ft_read(0, read_buff, 1024);
		my_errno = errno;
		printf("%s", read_buff);
		printf("res = %d and errno = %d\n", my_res, my_errno);
		if (my_errno)
		{
			++error_cpt;
			printf("Error: %s\n", strerror(my_errno));
		}
	}

	errno = 0;
	fd = open(file_name,  O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		printf("Test error, can't create test_to_dell.txt\n");
	else
	{
		write(fd, str_ref, strlen(str_ref));
		close(fd);
		
		printf("\nTest on valid file:\n");
		res_ref = strlen(str_ref);
		errno_ref = 0;
		fd = open(file_name, O_RDONLY);
		my_res = ft_read(fd, read_buff, 1024);
		my_errno = errno;
		printf(" res:%d, errno = %d\n", my_res, my_errno);
		close(fd);
		if (my_res != res_ref || my_errno != errno_ref)
		{
			printf("ko: expected res = %d, errno = %d\n", res_ref, errno_ref);
			++error_cpt;
		}
		else if (strcmp(read_buff, str_ref))
		{
			++error_cpt;
			printf("ko: read \"%s\" instead of \"%s\"\n", read_buff, str_ref);
		}
		else
			printf("ok\n");

		printf("\nTest on WRITE file:\n");
		fd = open(file_name, O_WRONLY | O_APPEND);
		errno = 0;
		res_ref = read(fd, read_buff, 1024); //wrong open, no rights
		errno_ref = errno;
		errno = 0;
		my_res = ft_read(fd, read_buff, 1024); //wrong open, no rights
		my_errno = errno;
		printf(" res:%d, errno = %d\n", my_res, my_errno);
		close(fd);
		if (my_res != res_ref || my_errno != errno_ref)
		{
			++error_cpt;
			printf("ko: expected res = %d, errno = %d\n", res_ref, errno_ref);
		}
		else if (strcmp(read_buff, str_ref))
		{
			++error_cpt;
			printf("ko: read \"%s\" instead of \"%s\"\n", read_buff, str_ref);
		}
		else
			printf("ok\n");

		remove(file_name);
	}

	printf("\nResults: %d error(s)\n", error_cpt);
	printf("--- End ---\n\n");
}