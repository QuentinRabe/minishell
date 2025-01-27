NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g -I./includes -I./libft
LDFLAGS	=	-L./libft -lft -lreadline
SRCS	=	$(shell find srcs execution -name '*.c') main.c
O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

BLUE	=	\033[1;36m
RED		=	\033[0;31m
NC		=	\033[0m
MAX_MESSAGE_LEN		:=	40

define compilation_progress
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)
	@printf "$(BLUE)[Minishell] Compiling sources⏳$(NC)";
	@printf "%*s" $(MAX_MESSAGE_LEN) "";
	@printf "\r";
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
		@printf "$(BLUE)[Minishell] Objects removed✅$(NC)";
		@printf "%*s" $(MAX_MESSAGE_LEN) "";
		@printf "\n";
		@rm -rf $(O_DIR)

fclean	:	clean
		@make fclean -sC ./libft
		@printf "$(BLUE)[Minishell] Executable removed✅$(NC)";
		@printf "%*s" $(MAX_MESSAGE_LEN) "";
		@printf "\n";
		@rm -f $(NAME)

msh_val	:	all
		@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
re		:	fclean all
