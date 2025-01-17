NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g -I./includes/ -I./libft/
SRCS	=	$(shell find srcs libft pipex -name '*.c') main.c
O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

GREEN	=	\033[0;32m
RED		=	\033[0;31m
NC		=	\033[0m # No Color

$(O_DIR)/%.o		:	%.c
		@mkdir -p $(dir $@)
		@echo -n "Compiling $<... "
		@$(CC) $(CFLAGS) -c $< -o $@  && echo -e "$(GREEN)[OK]$(NC)" || echo -e "$(RED)[FAIL]$(NC)"

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		@echo "Building $(NAME)..."
		@echo "--------------------"
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline && echo -e "$(GREEN)Build successful!$(NC)" || echo -e "$(RED)Build failed!$(NC)"

clean	:
		@echo "Cleaning object files..."
		@rm -rf $(O_DIR) && echo -e "$(GREEN)Cleaned!$(NC)" || echo -e "$(RED)Clean failed!$(NC)"

fclean	:	clean
		@echo "Removing executable..."
		@rm -f $(NAME) && echo -e "$(GREEN)Fully cleaned!$(NC)" || echo -e "$(RED)Full clean failed!$(NC)"

msh_val	:	all
		@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
re		:	fclean all
