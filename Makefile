NAME	= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g -I headers/ -I libft/libft.a
RM			= rm -rf

LIBFT		= -L libft -lft

HEADER		= minshell.h

MAIN		= main

BUILTINS	= is_builtin ft_cd ft_cd2 ft_echo ft_env ft_export ft_pwd ft_unset

DEBUG		= debug

PARSING		= quotation token tokens type

UTILS		= free print utils utils2

EXECUTION	= execution signals redirection

SRC			= $(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) \
			$(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
			$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
			$(addsuffix .c, $(addprefix src/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix src/debug/, $(DEBUG))) \
			$(addsuffix .c, $(addprefix src/execution/, $(EXECUTION))) \

OBJ			= $(SRC:c=o)
OBJ_DIR		= obj

all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
	@make -sC libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@touch src/debug/debugging.txt

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@make clean -C libft/
	@rm -f obj/$(OBJ)

fclean:
	@make fclean -C libft/
	@rm -f obj/*.o
	@rm -rf obj/
	@rm src/main/*.o src/builtins/*.o src/utils/*.o src/parsing/*.o src/execution/*.o src/debug/*.o
	@rm -f $(NAME)
	@rm -rf src/debug/debugging.txt

re:		fclean all

norm:
	@mv src/main/main.o src/debug/debug.o src/parsing/*.o src/builtins/*.o src/utils/*.o ./obj