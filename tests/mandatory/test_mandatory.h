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

int test_strlen();
int test_strcmp();
int test_strcpy();
int test_write();
int test_read(int test_std_in);
int test_read_automatic();
int test_strdup();

#endif