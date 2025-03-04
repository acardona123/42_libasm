#include "test_bonus.h"


char	log_file_name[100] = "test_mandatory_log.txt";
int		log_file_fd = -1;

void	logged_printf(bool printf_console, const char *format, ...)
{
	va_list	args;

	if (log_file_fd != -1)
	{
		va_start(args, format);
		vdprintf(log_file_fd, format, args);
		va_end(args);
	}
	if (printf_console)
	{
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

void	open_log_file()
{
	log_file_fd = open(log_file_name, O_CREAT | O_RDWR, 0666);
	if (log_file_fd == -1)
		printf("WARNING:\nFAIL TO OPEN THE LOG FILE\n\n");
}

void	close_log_file()
{
	if (log_file_fd != -1)
		close(log_file_fd);
}