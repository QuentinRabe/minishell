/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:17 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 20:36:41 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <data.h>
# include <messages.h>

// ==============INPUT_HANDLERS==============
bool	has_obvious_syntax_error(char *str);
bool	has_too_much_arrows(char *str);
char	**split_single_input(char *str);
bool	has_pipe(char *str);
// ==============TOKEN==============
t_token	*create_token_list(char **tokens);
// ==============UTILS==============
bool	is_space(char c);
bool	is_in(char *set, char c, int *index);
void	trim(char **str);
char	**ft_split_set(char *s, char *set);
void	print_list(t_token *head);

#endif // !MINISHELL_H
