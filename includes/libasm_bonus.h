#ifndef LIBASM_BONUS_H
# define LIBASM_BONUS_H

#include "libasm.h"

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

void ft_list_push_front(t_list **begin_list, void *data);

#endif