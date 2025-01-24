NAME			= libasm.a

CC				= nasm
ASM_FLAGS		= -O0 -f elf64 -g

ASM_SRC		= \
					ft_strcmp \
					ft_strlen

ASM_SRC_BONUS	= 

SRC_DIR			= mandatory/
ASM_FILES		= $(addprefix $(SRC_DIR), $(addsuffix .asm, $(ASM_SRC)))
ASM_FILES_BONUS	= $(addprefix $(SRC_DIR), $(addsuffix .asm, $(ASM_SRC_BONUS)))

OBJ_DIR			= obj/
OBJ_SRC			= $(patsubst $(SRC_DIR)%.asm, $(OBJ_DIR)%.o, $(ASM_FILES))
OBJ_BONUS		= $(patsubst $(SRC_DIR)%.asm, $(OBJ_DIR_BONUS)%.o, $(ASM_FILES_BONUS))

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
	@gcc -g mandatory/main.c $(OBJ_SRC) && ./a.out && rm a.out

debug: all
	@gcc -g mandatory/main.c $(OBJ_SRC) && gdb a.out
	@rm a.out

clean:
	@rm -f $(OBJ_SRC) $(OBJ_BONUS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean  bonus
