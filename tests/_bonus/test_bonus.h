#ifndef TEST_BONUS_H
# define TEST_BONUS_H

#include "../../includes/libasm_bonus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// test_list_display.c
void test_print_lst(t_list *lst_head);
void test_print_lst_str(t_list *lst_head);
void test_print_lst_int(t_list *lst_head);
void test_print_lst_int_silent(t_list *lst_head);

//test_list_tools.c
t_list	*generate_list_int(int size);
t_list	*list_new_elem_int(int data_value);
t_list	*list_dup_int(t_list *list_src);
void	list_free(t_list *list_head);
int		list_size_c(t_list *lst);


int	test_list_push_front();
int	test_list_size();
int	test_list_remove_if();
int	test_list_sort();
int	test_atoi_base();


#endif