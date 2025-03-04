#include "test_bonus.h"

static int	_test_sort_empty_list();
static	int _test_random_non_empty_lists(int number_of_tests, int list_len_max);

int	test_list_sort()
{
	int	number_of_tests = 50;
	int	list_len_max	= 100;
	int	error_cpt;

	logged_printf(true, "=== Tests of ft_list_sort ===\n\n");

	error_cpt = 0;
	error_cpt += _test_sort_empty_list();
	error_cpt += _test_random_non_empty_lists(number_of_tests, list_len_max);

	logged_printf(true, "\n-----------\nRESULTS: ");
	if (error_cpt)
		logged_printf(true, "Failure : %d error%s\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		logged_printf(true, "Success\n");
	logged_printf(true, "--- End ---\n");
	return error_cpt != 0;
}

int int_cmp(void *int1, void *int2)
{
	return *(int *)int1 - *(int *)int2;
}


// ==== Empty list ====
static int	_test_sort_empty_list()
{
	t_list *list;

	logged_printf(true, "- Test empty list:\n");
	list = NULL;
	ft_list_sort(&list, int_cmp);
	if (list)
	{
		logged_printf(true, "==> KO: Error while trying to sort an empty list (/!\\ Possible source of leaks)\n");
		return 1;
	}
	logged_printf(true, "==> OK\n");
	return 0;
}


// ==== Random non-empty list ====

static int	_test_sorting_one_list_int(int list_size);

static	int _test_random_non_empty_lists(int number_of_tests, int list_len_max)
{
	int error;

	logged_printf(true, "- Test on %d random lists (size max = %d):\n", number_of_tests, list_len_max);
	error = 0;
	for (int i = 0; i < number_of_tests; ++i)
		error += _test_sorting_one_list_int(1 + rand()%list_len_max);
	if (!error)
		logged_printf(true, "==> OK\n");
	else
		logged_printf(true, "==> KO: %d / %d errors in the multiple random lists test\n", error, number_of_tests);
	return error;
}


static int	_generate_to_identical_lists_int(t_list **lst1, t_list **lst2, int list_size);
static int _check_and_display_error(int list_size, t_list *list_initial, t_list *list_sorted);

static int	_test_sorting_one_list_int(int list_size)
{
	t_list	*list;
	t_list	*list_sorted;
	int		error;

	if (_generate_to_identical_lists_int(&list, &list_sorted, list_size))
		return 0;
	ft_list_sort(&list_sorted, int_cmp);
	error = _check_and_display_error(list_size, list, list_sorted);
	list_free(list);
	list_free(list_sorted);
	return error;
}


static int	_generate_to_identical_lists_int(t_list **lst1, t_list **lst2, int list_size)
{
	*lst1 = generate_list_int(list_size);
	*lst2 = list_dup_int(*lst1);
	if (!*lst1 || !*lst2)
	{
		list_free(*lst1);
		logged_printf(true, "WARNING: malloc fail durring list generation in _test_sorting_one_list_int, test aborted\n");
		return 1;
	}
	return 0;
}


int	check_list_int_is_sorted(t_list *begin_list, char *error_msg);
int	check_sorted_list_size(t_list *sorted_list, int expected_len, char *err_msg);

static int _check_and_display_error(int list_size, t_list *list_initial, t_list *list_sorted)
{
	char	error_msg_sorted[128];
	char	error_msg_len[128];
	int		error;

	error = check_list_int_is_sorted(list_sorted, error_msg_sorted);
	error |= check_sorted_list_size(list_sorted, list_size_c(list_initial), error_msg_len);

	logged_printf(error, " Test (%s):\n  src: (size = %d) ", error ? "KO":"OK", list_size);
	test_print_lst_int_silent(error, list_initial);
	logged_printf(error, "  res: ");
	test_print_lst_int_silent(error, list_sorted);
	logged_printf(error, "  => %s\n  => %s\n ==> %s\n", error_msg_sorted, error_msg_len, error ? "KO":"OK");

	return error;
}

int	check_list_int_is_sorted(t_list *begin_list, char *error_msg)
{
	int	last_value;
	int	curr_value;

	if (!begin_list)
		return 0;
	last_value = *(int *)begin_list->data;
	begin_list = begin_list->next;
	while (begin_list)
	{
		curr_value = *(int *)begin_list->data;
		if (curr_value < last_value)
		{
			sprintf(error_msg, "Not sorted: %d before %d.", last_value, curr_value);
			return (1);
		}
		last_value = curr_value;
		begin_list = begin_list->next;
	}
	sprintf(error_msg, "Properly sorted.");
	return 0;
}

int	check_sorted_list_size(t_list *sorted_list, int expected_len, char *err_msg)
{
	int	len_sorted;

	len_sorted = list_size_c(sorted_list);
	if (len_sorted != expected_len)
	{
		sprintf(err_msg, "Wrong list size: %d insted of %d.", len_sorted, expected_len);
		return 1;
	}
	sprintf(err_msg, "Proper size.");
	return 0;
}
