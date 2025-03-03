#include "test_mandatory.h"

static int	_test_read_stdin();
static int	_test_read_valid_file();
static int	_test_read_write_only_file();

int test_read_automatic()
{
	return test_read(0);
}


int test_read(int test_std_in)
{
	int	error_cpt;

	int 	fd;
	char	file_name[] = "test_to_dell.txt";
	char	read_buff[1024];
	char	str_ref[] = "This is a test\n";
	int		res_ref;
	int 	errno_ref;
	int 	my_res;
	int		my_errno;


	printf("=== Tests of ft_read ===\n\n");

	error_cpt = 0;
	if (test_std_in)
		error_cpt += _test_read_stdin();
	error_cpt += _test_read_valid_file();
	error_cpt += _test_read_write_only_file();
	
	printf("\n-----------\nRESULTS: ");
	if (error_cpt)
		printf("Failure : %d error%s\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		printf("Success\n");
	printf("--- End ---\n");
	return error_cpt != 0;
}

static int	_test_read_stdin()
{
	char	read_buff[1024];
	int 	my_res;
	int		my_errno;

	printf("-Manual test on stdin, write anything (less than 1024 char) and check if the printed text is equal to it:\n");
	errno = 0;
	my_res = ft_read(0, read_buff, 1024);
	my_errno = errno;
	printf(" input:\n\"%s\"", read_buff);
	printf(" - res = %d\n - errno = %d\n", my_res, my_errno);
	if (my_errno)
	{
		printf(" => Error (errno not null): %s\n", strerror(my_errno));
		return 1;
	}
	printf(" => OK ( /!\\ MANUAL CHECK TO DO BY COMPARING THE VALUES ABOVE )\n");
	return 0;
}


typedef struct s_read_results
{
	char	*str;
	int		ret;
	int 	errno_value;
}	s_read_results;

static int	_create_and_open_file(char *file_name, char *content, int open_flags);
static int	_cmp_read_results(s_read_results expected, s_read_results obtained);

int	_test_read_valid_file()
{
	char			file_name[] = ".test_valid_file_to_dell.txt";
	char			content[] = "This is the content of a test\nWith two lines.";
	int				fd;
	char			read_buff[1024] = {};
	s_read_results	expected;
	s_read_results	obtained;

	printf("- Test on valid non-empty file:\n");

	fd = _create_and_open_file(file_name, content, O_RDONLY);
	if (fd == -1)
	{
		printf("Warning: Test aborted can't create a valid file.\n");
		return 0;
	}

	expected.str = content;
	expected.ret = strlen(content);
	expected.errno_value = 0;
	errno = 0;
	obtained.ret = ft_read(fd, read_buff, 1024);
	obtained.str = read_buff;
	obtained.errno_value = errno;

	close(fd);
	remove(file_name);

	return _cmp_read_results(expected, obtained);
}

static int	_test_read_write_only_file()
{
	char			file_name[] = ".test_wronly_file_to_dell.txt";
	char			content[] = "This is the content of a test\nWith two lines.";
	int				fd;
	char			ft_read_buff[1024] = {};
	char			read_buff[1024] = {};
	s_read_results	expected;
	s_read_results	obtained;

	printf("- Test on WRITE_ONLY file:\n");

	fd = _create_and_open_file(file_name, content, O_WRONLY | O_APPEND); //will not be readable
	if (fd == -1)
	{
		printf("Warning: Test aborted can't create a valid file.\n");
		return 0;
	}

	errno = 0;
	expected.str = NULL;
	expected.ret = read(fd, read_buff, 1024);	//real read that will fail because of wrong permissions
	expected.errno_value = errno;
	
	errno = 0;
	obtained.str = ft_read_buff;
	obtained.ret = ft_read(fd, ft_read_buff, 1024);
	obtained.errno_value = errno;

	close(fd);
	remove(file_name);

	return _cmp_read_results(expected, obtained);
}

static int	_create_valid_file(char *file_name, char *content)
{
	int	fd;

	fd = open(file_name,  O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return 1;
	write(fd, content, strlen(content));
	close(fd);
	return 0;
}

static int	_create_and_open_file(char *file_name, char *content, int open_flags)
{
	int	fd;

	if (_create_valid_file(file_name, content))
		return -1;
	fd = open(file_name, open_flags);
	if (fd == -1)
		remove(file_name);
	return fd;
}

static int	_cmp_read_results(s_read_results expected, s_read_results obtained)
{
	if (obtained.ret != expected.ret
		|| obtained.errno_value != expected.errno_value
		|| (!obtained.errno_value
			&& ((obtained.str && !expected.str)
				|| (!obtained.str && expected.str)
				|| (obtained.str && expected.str && strcmp(obtained.str, expected.str)))
			))
	{
		printf("==> KO:\n");
		printf("  - return value:\n     Expected: %d\n     Obtained: %d\n", expected.ret, obtained.ret);
		printf("  - errno value:\n     Expected: %d\n     Obtained: %d\n", expected.errno_value, obtained.errno_value);
		if (obtained.ret != expected.ret || obtained.errno_value != expected.errno_value)
			printf("  - string content: not evaluated\n");
		else
		{
			printf("  - string content: KO\n");
			printf("     Expected: \"%s\"\n     Obtained: \"%s\"\n", expected.str, obtained.str);
		}
		return 1;
	}
	printf("==> ok\n");
	return 0;
}