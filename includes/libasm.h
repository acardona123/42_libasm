#ifndef LIBASM_H
# define LIBASM_H

#include <unistd.h>

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
ssize_t	ft_read(int fd, void *buf, size_t count);
ssize_t	ft_write(int fd, const void *buf, size_t count);
char	*ft_strdup(const char *s);


typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

#endif