/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:11:50 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 13:59:31 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int		get_len(char *store);
int		contain_newline(char *str);
int		ft_strlen_gnl(char *str, char c);
char	*get_next_line(int fd);
char	*clean_store(char *store);
char	*extract_line(char *store);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*fill_store(int fd, char *store);
#endif
