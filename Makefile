NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -I./includes/ -I./libft/
SRCS	=	$(shell find srcs -name '*.c') main.c
O_DIR	=	objs
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
		@echo "Making libft..."
		@make -sC ./libft
		@echo "--------------------"
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline -L./libft -lft && echo -e "$(GREEN)Build successful!$(NC)" || echo -e "$(RED)Build failed!$(NC)"

clean	:
		@echo "Cleaning object files..."
		@make clean -sC ./libft
		@rm -rf $(O_DIR) && echo -e "$(GREEN)Cleaned!$(NC)" || echo -e "$(RED)Clean failed!$(NC)"

fclean	:	clean
		@echo "Removing executable..."
		@make fclean -sC ./libft
		@rm -f $(NAME) && echo -e "$(GREEN)Fully cleaned!$(NC)" || echo -e "$(RED)Full clean failed!$(NC)"

msh_val	:	all
		valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./$(NAME)

re		:	fclean all
