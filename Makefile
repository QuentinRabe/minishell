NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g -I./includes -I./libft
LDFLAGS	=	-L./libft -lft -lreadline
SRCS	=	srcs/heredoc/signal.c\
srcs/heredoc/utils.c\
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
./main.c

O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

DIR		=	$(wildcard $(O_DIR))
FILE	=	$(wildcard $(NAME))

BLUE	=	\033[1;36m
RED		=	\033[0;31m
NC		=	\033[0m
MAX_MESSAGE_LEN		:=	100

define compilation_progress
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)
	@printf "$(BLUE)[Minishell] Compiling sources⏳$(NC)";
	@printf "%*s" $(MAX_MESSAGE_LEN) "";
	@printf "\r";
endef

define clean
	@if [ -z "$(DIR)" ]; then \
		printf "$(BLUE)[Minishell] No objects to remove$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
	else \
		printf "$(BLUE)[Minishell] Objects removed✅$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
		rm -rf $(O_DIR);\
	fi
endef

define fclean
	@if [ -z "$(FILE)" ]; then \
		printf "$(BLUE)[Minishell] No executable to remove$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
	else \
		printf "$(BLUE)[Minishell] Executable removed✅$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
		rm -f $(NAME);\
	fi
endef

$(O_DIR)/%.o		:	%.c
		@mkdir -p $(dir $@)
		$(compilation_progress)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		@make -sC ./libft
		@$(CC) $(CFLAGS)  $(SRCS) -o $(NAME) -L./libft -lft -lreadline && printf "$(BLUE)[Minishell] Success✅$(NC)" || printf "$(RED)[Minishell] Failure😩$(NC)"
		@printf "\n";

clean	:
		@make clean -sC ./libft
		$(clean)
		@sleep 0.5

fclean	:	clean
		@make fclean -sC ./libft
		$(fclean)
		@sleep 0.5

msh_val	:	all
		@valgrind --suppressions=readline.supp --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
re		:	fclean all
