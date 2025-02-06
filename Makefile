# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 12:48:11 by arabefam          #+#    #+#              #
#    Updated: 2025/02/06 06:57:11 by arabefam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I./includes -I./libft
LDFLAGS	=	-L./libft -lft -lreadline
SRCS	=	srcs/heredoc/signal.c\
srcs/heredoc/utils.c\
srcs/heredoc/utils_1.c\
srcs/heredoc/heredoc.c\
srcs/redir/build_1.c\
srcs/redir/build.c\
srcs/redir/build_2.c\
srcs/environment/getenv.c\
srcs/environment/env.c\
srcs/environment/sort.c\
srcs/environment/envp.c\
srcs/input_handlers/formating_utils.c\
srcs/input_handlers/token.c\
srcs/input_handlers/error_2.c\
srcs/input_handlers/parse_utils.c\
srcs/input_handlers/split_mutli.c\
srcs/input_handlers/split_single.c\
srcs/input_handlers/error.c\
srcs/input_handlers/error_1.c\
srcs/input_handlers/formating.c\
srcs/input_handlers/token_multi_input.c\
srcs/input_handlers/token_single_input.c\
srcs/history/history.c\
srcs/utils/utils_4.c\
srcs/utils/utils_3.c\
srcs/utils/utils_1.c\
srcs/utils/utils_2.c\
srcs/utils/ft_split_set.c\
srcs/argv/quotes.c\
srcs/argv/build.c\
srcs/expansion/expander.c\
srcs/expansion/utils_heredoc.c\
srcs/expansion/utils_1.c\
srcs/expansion/heredoc.c\
srcs/expansion/utilis_2.c\
srcs/expansion/utils.c\
srcs/gnl/get_next_line.c\
srcs/gnl/get_next_line_utils.c\
execution/builtins_ft_3.c\
execution/builtins_ft_1.c\
execution/execution.c\
execution/ft_free.c\
execution/utils2.c\
execution/utils3.c\
execution/ft_error.c\
execution/builtins_ft_2.c\
execution/builtins_ft.c\
execution/execute.c\
execution/utils.c\
execution/my_shell.c\
execution/builtins_ft_4.c\
execution/export_utils.c\
execution/exit_utils.c\
execution/execute_utils.c\
execution/cd_utils.c\
./main.c

O_DIR	=	objs_dir

OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

$(O_DIR)/%.o		:	%.c
		@touch .msh_history
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		make -C ./libft
		$(CC) $(CFLAGS)  $(SRCS) -o $(NAME) $(LDFLAGS)

clean	:
		make clean -C ./libft
		rm -rf $(O_DIR)
		rm -f .msh_history
fclean	:	clean
		make fclean -C ./libft
		rm -f $(NAME)

msh_val	:	all
		@valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes ./$(NAME)
re		:	fclean all

.PHONY	:	all fclean clean re msh_val
