NAME			= libasm.a

CC				= nasm
ASM_FLAGS		= -g -f elf64 -O0

ASM_SRC			= \
					ft_strcmp \
					ft_strcpy \
					ft_strlen \
					ft_write \
					ft_read \
					ft_strdup

ASM_SRC_BONUS	= \
					ft_list_push_front

TEST_SRC		= \
					test_ft_read \
					test_ft_write \
					test_ft_strcpy \
					test_ft_strcmp \
					test_ft_strlen \
					test_ft_strdup
TEST_SRC_BONUS		= \
					test_ft_list_push_front

SRC_DIR					=	srcs/
SRC_MANDATORY_SUBDIR	=	mandatory/
ASM_FILES				=	$(addprefix $(SRC_DIR)$(SRC_MANDATORY_SUBDIR), $(addsuffix .s, $(ASM_SRC)))
SRC_BONUS_SUBDIR		=	_bonus/
ASM_FILES_BONUS			=	$(addprefix $(SRC_DIR)$(SRC_BONUS_SUBDIR), $(addsuffix .s, $(ASM_SRC_BONUS)))

OBJ_DIR					=	obj/
OBJ_SRC					=	$(patsubst $(SRC_DIR)%.s, $(OBJ_DIR)%.o, $(ASM_FILES))
OBJ_BONUS				=	$(patsubst $(SRC_DIR)%.s, $(OBJ_DIR)%.o, $(ASM_FILES_BONUS))

TEST_DIR				=	tests/
TEST_MANDATORY_SUBDIR	=	mandatory/
TEST_FILES_MANDATORY	=	$(addprefix $(TEST_DIR)$(TEST_MANDATORY_SUBDIR), $(addsuffix .c, main $(TEST_SRC)))
TEST_BONUS_SUBDIR		=	_bonus/
TEST_FILES_BONUS		=	$(addprefix $(TEST_DIR)$(TEST_MANDATORY_SUBDIR), $(addsuffix .c, $(TEST_SRC))) \
							$(addprefix $(TEST_DIR)$(TEST_BONUS_SUBDIR), $(addsuffix .c, main_bonus $(TEST_SRC_BONUS)))

all: ${NAME}

$(OBJ_DIR)%.o: $(SRC_DIR)%.s $(DEPS)
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(ASM_FLAGS) $< -o $@


${NAME}: $(OBJ_SRC)
	ar rcs $(NAME) ${OBJ_SRC}


test: all
	@gcc -g -O0 $(TEST_FILES_MANDATORY) -L. -lasm && ./a.out && rm a.out

test_v: all
	@gcc -g -O0 $(TEST_FILES_MANDATORY) -L. -lasm && valgrind ./a.out && rm a.out

debug: all
	@gcc -g -O0 $(TEST_FILES_MANDATORY) -L. -lasm && gdb a.out
	@rm a.out


bonus : $(OBJ_SRC) $(OBJ_BONUS) 
	ar rcs $(NAME) ${OBJ_SRC} $(OBJ_BONUS)

bonus_test: bonus
	@gcc -g -O0 $(TEST_FILES_BONUS) -L. -lasm && ./a.out && rm a.out

bonus_test_v: bonus
	@gcc -g -O0 $(TEST_FILES_BONUS) -L. -lasm && valgrind ./a.out && rm a.out

bonus_debug: bonus
	@gcc -g -O0 $(TEST_FILES_BONUS) -L. -lasm && gdb a.out
	@rm a.out

clean:
	@rm -rf $(OBJ_DIR)


fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean  bonus
