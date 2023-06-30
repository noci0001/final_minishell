NAME	= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I headers/ -I libft/libft.a
RM			= rm -rf

LIBFT		= -L libft -lft

HEADER		= minshell.h

MAIN		= main

BUILTINS	= ft_cd ft_echo ft_env ft_export ft_pwd

DEBUG		= debug

PARSING		= quotation token tokens type

UTILS		= free print utils

SRC			= $(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) \
			$(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
			$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
			$(addsuffix .c, $(addprefix src/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix src/debug/, $(DEBUG))) \

OBJ			= $(SRC:c=o)
OBJ_DIR		= obj

all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
	@make -sC libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@mv src/main/main.o src/debug/debug.o src/parsing/*.o src/builtins/*.o src/utils/*.o ./obj
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
	@rm -f obj/$(OBJ)
	@rm -f $(NAME)
	@rm -rf src/debug/debugging.txt

re:		fclean all