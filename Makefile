NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -I./includes/ -I./libft/
SRCS	=	$(shell find srcs -name '*.c') main.c
OBJS	=	$(SRCS:.c=.o)

%.o		:	%.c
		@$(CC) $(CFLAGS) -c -o $@ $<

all		:	$(NAME)
$(NAME)	:	$(OBJS)
		@make -sC ./libft
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline -L./libft -lft
clean	:
		@make clean -sC ./libft
		@rm -f $(OBJS)
fclean	:	clean
		@make fclean -sC ./libft
		@rm -f $(NAME)
re		:	fclean all
