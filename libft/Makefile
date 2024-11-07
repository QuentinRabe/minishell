NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
SRCS	=	$(wildcard ./*.c)
OBJS	=	$(SRCS:.c=.o)

GREEN	=	\033[0;32m
RED		=	\033[0;31m
NC		=	\033[0m # No Color

./%.o	:	./%.c
		@echo -n "Compiling $<... "
		@$(CC) $(CFLAGS) -c $< -o $@ && echo -e "$(GREEN)[OK]$(NC)" || echo -e "$(RED)[FAIL]$(NC)"

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		@echo "Building $(NAME)..."
		@ar -rcs $(NAME) $(OBJS) && echo -e "$(GREEN)Build successful!$(NC)" || echo -e "$(RED)Build failed!$(NC)"

clean	:
		@echo "Cleaning object files..."
		@$(RM) $(OBJS) && echo -e "$(GREEN)Cleaned!$(NC)" || echo -e "$(RED)Clean failed!$(NC)"

fclean	:	clean
		@echo "Removing executable..."
		@$(RM) $(NAME) && echo -e "$(GREEN)Fully cleaned!$(NC)" || echo -e "$(RED)Full clean failed!$(NC)"

re	:	fclean all
