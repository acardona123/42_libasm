NAME			= libasm.a

CC				= nasm
ASM_FLAGS		= -g -f elf64 -O0

# === SOURCES ===

ASM_SRC_MANDATORY	=	\
						ft_strcmp \
						ft_strcpy \
						ft_strlen \
						ft_write \
						ft_read \
						ft_strdup \

ASM_SRC_BONUS		=	\
						ft_list_push_front \
						ft_list_size \
						ft_list_remove_if \
						ft_list_sort \
						ft_atoi_base \

SRC_DIR					=	srcs/
SRC_SUBDIR_MANDATORY	=	mandatory/
SRC_SUBDIR_BONUS		=	_bonus/

ASM_FILES_MANDATORY		=	$(addprefix $(SRC_DIR)$(SRC_SUBDIR_MANDATORY), $(addsuffix .s, $(ASM_SRC_MANDATORY)))
ASM_FILES_BONUS			=	$(addprefix $(SRC_DIR)$(SRC_SUBDIR_BONUS), $(addsuffix .s, $(ASM_SRC_BONUS)))


# === OBJECTS ===

OBJ_DIR					=	obj/
OBJ_MANDATORY			=	$(patsubst $(SRC_DIR)%.s, $(OBJ_DIR)%.o, $(ASM_FILES_MANDATORY))
OBJ_BONUS				=	$(patsubst $(SRC_DIR)%.s, $(OBJ_DIR)%.o, $(ASM_FILES_BONUS))


# === TESTS ===

TEST_SRC_MANDATORY	=	\
						test_mandatory_main \
						test_display_results \
						test_ft_read \
						test_ft_write \
						test_ft_strcpy \
						test_ft_strcmp \
						test_ft_strlen \
						test_ft_strdup \
						test_log_management \

TEST_SRC_BONUS		=	\
						test_bonus_main \
						test_display_results \
						test_ft_list_push_front \
						test_ft_list_remove_if \
						test_ft_list_size \
						test_ft_list_sort \
						test_ft_atoi_base \
						test_list_display \
						test_list_tools \
						test_log_management \

TEST_SRC_MANUAL		=	\
						test_manual_main \

TEST_DIR				=	tests/
TEST_SUBDIR_MANDATORY	=	mandatory/
TEST_SUBDIR_BONUS		=	_bonus/
TEST_SUBDIR_MANUAL		=	manual/

TEST_FILES_MANDATORY	=	$(addprefix $(TEST_DIR)$(TEST_SUBDIR_MANDATORY),	$(addsuffix .c, $(TEST_SRC_MANDATORY)))
TEST_FILES_BONUS		=	$(addprefix $(TEST_DIR)$(TEST_SUBDIR_BONUS),		$(addsuffix .c, $(TEST_SRC_BONUS)))
TEST_FILES_MANUAL		=	$(addprefix $(TEST_DIR)$(TEST_SUBDIR_MANUAL),		$(addsuffix .c, $(TEST_SRC_MANUAL)))


# === RULES ===


all: ${NAME}

$(OBJ_DIR)%.o: $(SRC_DIR)%.s $(DEPS)
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(ASM_FLAGS) $< -o $@


${NAME}: $(OBJ_MANDATORY)
	ar rcs $(NAME) ${OBJ_MANDATORY}


test: all
	@gcc -g -O0 $(TEST_FILES_MANDATORY) -L. -lasm && ./a.out && rm a.out

test_v: all
	@gcc -g -O0 $(TEST_FILES_MANDATORY) -L. -lasm && valgrind ./a.out && rm a.out

debug: all
	@gcc -g -O0 $(TEST_FILES_MANDATORY) -L. -lasm && gdb a.out
	@rm a.out


bonus : $(OBJ_MANDATORY) $(OBJ_BONUS) 
	ar rcs $(NAME) ${OBJ_MANDATORY} $(OBJ_BONUS)

bonus_test: bonus
	@gcc -g -O0 $(TEST_FILES_BONUS) -L. -lasm && ./a.out && rm a.out

bonus_test_v: bonus
	@gcc -g -O0 $(TEST_FILES_BONUS) -L. -lasm && valgrind ./a.out && rm a.out

bonus_debug: bonus
	@gcc -g -O0 $(TEST_FILES_BONUS) -L. -lasm && gdb a.out
	@rm a.out

manual_test: bonus
	@gcc -g -O0 $(TEST_FILES_MANUAL) -L. -lasm && ./a.out
	@rm a.out

clean:
	@rm -rf $(OBJ_DIR)


fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean  bonus
