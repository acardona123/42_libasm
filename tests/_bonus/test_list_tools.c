#include "test_bonus.h"


t_list *generate_list_int(int size)
{
	t_list	*lst;
	t_list	*old_lst;
	int		*data;

	lst = NULL;
	old_lst = NULL;

	srand(time(NULL));
	for (int i = 0; i <  size; ++i)
	{
		data = malloc(sizeof(int));
		if (!data)
		{
			logged_printf(true, "WARNING: malloc fail in generate_list_int -> list shorten\n");
			return lst;
		}
		*data = rand()%100 - 50;
		ft_list_push_front(&lst, data);
		if (old_lst == lst) //test if ft_list_push_front worked, otherwise the malloc inside it failed
		{
			logged_printf(true, "WARNING: malloc fail in generate_list_int -> list shorten\n");
			free(data);
			return lst;
		}
		old_lst = lst;
	}
	return lst;
}

t_list	*list_new_elem_int(int data_value)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->data = malloc(sizeof(int));
	if (!new_elem->data)
	{
		free(new_elem);
		return (NULL);
	}
	new_elem->next = NULL;
	*(int *)(new_elem->data) = data_value;
	return new_elem;
}

t_list	*list_dup_int(t_list *list_src)
{
	t_list	*list_dup_head;
	t_list	*list_dup_last;

	if (!list_src)
		return NULL;
	list_dup_head = list_new_elem_int(*(int *)list_src->data);
	if (!list_dup_head)
		return NULL;
	list_dup_last = list_dup_head;
	list_src = list_src->next;
	while (list_src)
	{
		list_dup_last->next = list_new_elem_int(*(int *)list_src->data);
		if (!list_dup_last->next)
		{
			list_free(list_dup_head);
			return NULL;
		}
		list_dup_last = list_dup_last->next;
		list_src = list_src->next;
	}
	return list_dup_head;
}

void	list_free(t_list *list_head)
{
	t_list	*elem;
	t_list	*next_elem;

	elem = list_head;
	while (elem)
	{
		free(elem->data);
		next_elem = elem->next;
		free(elem);
		elem = next_elem;
	}
}

int	list_size_c(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		++i;
		lst = lst->next;
	}
	return i;
}

int	test_list_and_display_results(char *test_description, int (*test_function)(bool print_details))
{
	logged_printf(true, "- %s:\n", test_description);
	if ((*test_function)(false))
	{
		logged_printf(true, "KO\n");
		(*test_function)(true);
		return 1;
	}
	logged_printf(true, "OK\n");
	return 0;
}