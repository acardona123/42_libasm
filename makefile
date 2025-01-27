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

ASM_SRC_BONUS	= 

TEST_SRC		= \
					main \
					test_ft_read \
					test_ft_write \
					test_ft_strcpy \
					test_ft_strcmp \
					test_ft_strlen \
					test_ft_strdup

SRC_DIR			= mandatory/
ASM_FILES		= $(addprefix $(SRC_DIR), $(addsuffix .asm, $(ASM_SRC)))
ASM_FILES_BONUS	= $(addprefix $(SRC_DIR), $(addsuffix .asm, $(ASM_SRC_BONUS)))

OBJ_DIR			= obj/
OBJ_SRC			= $(patsubst $(SRC_DIR)%.asm, $(OBJ_DIR)%.o, $(ASM_FILES))
OBJ_BONUS		= $(patsubst $(SRC_DIR)%.asm, $(OBJ_DIR_BONUS)%.o, $(ASM_FILES_BONUS))

TEST_DIR		= tests/
TEST_FILES		= $(addprefix $(TEST_DIR), $(addsuffix .c, $(TEST_SRC)))

all: ${NAME}

$(OBJ_DIR)%.o: $(SRC_DIR)%.asm $(DEPS)
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(ASM_FLAGS) $< -o $@


${NAME}: $(OBJ_SRC)
	ar rcs $(NAME) ${OBJ_SRC}

bonus : $(OBJ_SRC) $(OBJ_BONUS) 
	ar rcs $(NAME) ${OBJ_SRC} $(OBJ_BONUS)

test: all
	@gcc -g -O0 $(TEST_FILES) -L. -lasm && ./a.out && rm a.out

test_v: all
	@gcc -g -O0 $(TEST_FILES) -L. -lasm && valgrind ./a.out && rm a.out

debug: all
	@gcc -g -O0 $(TEST_FILES) -L. -lasm && gdb a.out
	@rm a.out

clean:
	@rm -f $(OBJ_SRC) $(OBJ_BONUS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean  bonus
