# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 07:04:28 by arabefam          #+#    #+#              #
#    Updated: 2025/02/06 07:15:15 by arabefam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
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

$(O_DIR)/%.o		:	%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		ar -rcs $(NAME) $(OBJS)

clean	:
		rm -rf $(O_DIR)

fclean	:	clean
		rm -f $(NAME)

re		:	fclean all

.PHONY	:	all fclean clean re
