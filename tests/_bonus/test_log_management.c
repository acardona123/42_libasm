#include "test_bonus.h"


char	log_file_name[128];
int		log_file_fd = -1;

void	logged_printf(bool print_stdout, const char *format, ...)
{
	va_list	args;

	if (log_file_fd != -1)
	{
		va_start(args, format);
		vdprintf(log_file_fd, format, args);
		va_end(args);
	}
	if (print_stdout)
	{
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

void	open_log_file(char *new_log_file_name)
{
	if (new_log_file_name)
	{
		strncpy(log_file_name, new_log_file_name, 127);
		log_file_name [127] = 0;
		log_file_fd = open(log_file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	}
	if (log_file_fd == -1)
		printf("WARNING:\nFAIL TO OPEN THE LOG FILE\n\n");
}

void	close_log_file()
{
	if (log_file_fd != -1)
		close(log_file_fd);
}