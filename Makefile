NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g -I./includes -I./libft
LDFLAGS	=	-L./libft -lft -lreadline
SRCS	=	$(shell find srcs execution -name '*.c') main.c
O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

DIR		=	$(wildcard $(O_DIR))
FILE	=	$(wildcard $(NAME))

BLUE	=	\033[1;36m
RED		=	\033[0;31m
NC		=	\033[0m
MAX_MESSAGE_LEN		:=	40

define compilation_progress
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)
	@printf "$(BLUE)[Minishell] Compiling sources⏳$(NC)";
	@printf "%*s" $(MAX_MESSAGE_LEN) "";
	@printf "\r";
	@sleep 0.1
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
		@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
re		:	fclean all
