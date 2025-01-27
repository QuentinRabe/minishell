# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 07:04:28 by arabefam          #+#    #+#              #
#    Updated: 2025/01/27 08:13:36 by arabefam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g
SRCS	=	$(shell find ./ -name '*.c')
O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

GREEN	=	\033[1;32m
RED		=	\033[0;31m
NC		=	\033[0m
MAX_MESSAGE_LEN := 40

define compilation_progress
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)[Libft] Compiling sources⏳$(NC)";
	@printf "%*s" $(MAX_MESSAGE_LEN) "";
	@printf "\r";
endef

$(O_DIR)/%.o		:	%.c
		@mkdir -p $(dir $@)
		$(compilation_progress)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		@printf "$(GREEN)[libft] Success✅$(2C)"
		@printf "%*s" $(MAX_MESSAGE_LEN) "";
		@printf "\r";
		@printf "\n";
		@ar -rcs $(NAME) $(OBJS)

clean	:
		@printf "$(GREEN)[Libft] Objects removed✅$(NC)";
		@printf "%*s" $(MAX_MESSAGE_LEN) "";
		@printf "\n";
		@rm -rf $(O_DIR)

fclean	:	clean
		@printf "$(GREEN)[Libft] Archive removed✅$(NC)";
		@printf "%*s" $(MAX_MESSAGE_LEN) "";
		@printf "\n";
		@rm -f $(NAME)
re		:	fclean all
