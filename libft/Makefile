# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 07:04:28 by arabefam          #+#    #+#              #
#    Updated: 2025/02/03 07:03:47 by arabefam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g
SRCS	=	./ft_strdup.c\
./ft_putstr_fd.c\
./ft_split.c\
./ft_strchr.c\
./ft_strlen_set.c\
./ft_atoi.c\
./ft_bzero.c\
./ft_calloc.c\
./ft_isalnum.c\
./ft_isalpha.c\
./ft_isascii.c\
./ft_isdigit.c\
./ft_isprint.c\
./ft_itoa.c\
./ft_lstadd_back_bonus.c\
./ft_lstadd_front_bonus.c\
./ft_lstclear_bonus.c\
./ft_lstdelone_bonus.c\
./ft_lstiter_bonus.c\
./ft_lstlast_bonus.c\
./ft_lstmap_bonus.c\
./ft_lstnew_bonus.c\
./ft_lstsize_bonus.c\
./ft_memchr.c\
./ft_memcmp.c\
./ft_memcpy.c\
./ft_memmove.c\
./ft_memset.c\
./ft_putchar_fd.c\
./ft_putendl_fd.c\
./ft_putnbr_fd.c\
./ft_tolower.c\
./ft_toupper.c\
./ft_strcmp.c\
./ft_strtrim.c\
./ft_striteri.c\
./ft_strjoin.c\
./ft_strlcat.c\
./ft_strlcpy.c\
./ft_strlen.c\
./ft_strmapi.c\
./ft_strncmp.c\
./ft_strnstr.c\
./ft_strrchr.c\
./ft_substr.c\

O_DIR	=	objs_dir
OBJS	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

DIR		=	$(wildcard $(O_DIR))
FILE	=	$(wildcard $(NAME))

GREEN	=	\033[1;32m
RED		=	\033[0;31m
NC		=	\033[0m
MAX_MESSAGE_LEN := 100

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
