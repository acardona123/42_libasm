#ifndef TEST_MANDATORY_H
# define TEST_MANDATORY_H

# include "../../includes/libasm.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <stdbool.h>
#include <stdarg.h>

//logs
extern char	log_file_name[128];
extern int	log_file_fd;
void		open_log_file(char *new_log_file_name);
void		close_log_file();
void		logged_printf(bool print_stdout, const char *format, ...);

int test_strlen();
int test_strcmp();
int test_strcpy();
int test_write();
int test_read(int test_std_in);
int test_read_automatic();
int test_strdup();

#endif