NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
SRCS	=	$(shell find ./ -name '*.c')
O_DIR	=	objs
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

GREEN	=	\033[0;32m
RED		=	\033[0;31m
NC		=	\033[0m # No Color

$(O_DIR)/%.o	:	%.c
		@mkdir -p $(dir $@)
		@echo -n "Compiling $<... "
		@$(CC) $(CFLAGS) -c $< -o $@ && echo -e "$(GREEN)[OK]$(NC)" || echo -e "$(RED)[FAIL]$(NC)"

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		@echo "Building $(NAME)..."
		@ar -rcs $(NAME) $(OBJS) && echo -e "$(GREEN)Build successful!$(NC)" || echo -e "$(RED)Build failed!$(NC)"

clean	:
		@echo "Cleaning object files..."
		@$(RM) -r $(O_DIR) && echo -e "$(GREEN)Cleaned!$(NC)" || echo -e "$(RED)Clean failed!$(NC)"

fclean	:	clean
		@echo "Removing executable..."
		@$(RM) $(NAME) && echo -e "$(GREEN)Fully cleaned!$(NC)" || echo -e "$(RED)Full clean failed!$(NC)"

re	:	fclean all
