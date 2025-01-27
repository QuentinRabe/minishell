# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 07:04:28 by arabefam          #+#    #+#              #
#    Updated: 2025/01/27 10:57:48 by arabefam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g
SRCS	=	$(shell find ./ -name '*.c')
O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

DIR		=	$(wildcard $(O_DIR))
FILE	=	$(wildcard $(NAME))

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

define clean
	@if [ -z "$(DIR)" ]; then \
		printf "$(GREEN)[Libft] No objects to remove$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
	else \
		printf "$(GREEN)[Libft] Objects removed✅$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
		rm -rf $(O_DIR);\
	fi
endef

define fclean
	@if [ -z "$(FILE)" ]; then \
		printf "$(GREEN)[Libft] No archive to remove$(NC)";\
		printf "%*s" $(MAX_MESSAGE_LEN) "";\
		printf "\n";\
	else \
		printf "$(GREEN)[Libft] Archive removed✅$(NC)";\
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
		@printf "$(GREEN)[libft] Success✅$(2C)"
		@printf "%*s" $(MAX_MESSAGE_LEN) "";
		@printf "\r";
		@printf "\n";
		@ar -rcs $(NAME) $(OBJS)

clean	:
		$(clean)
		@sleep 0.5
fclean	:	clean
		$(fclean)
		@sleep 0.5
re		:	fclean all
