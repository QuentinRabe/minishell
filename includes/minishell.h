/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:17 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/09 12:43:24 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <colors.h>
# include <stdbool.h>
# include <data.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*get_prompt_cwd(void);
char	**extract_path_from_env(char **env);
/*==========TOKEN==========*/
void	create_cmd_lst(char *input, t_msh *msh);
void	create_token_list(t_msh *msh);
int		count_quoted_pipe(char *str);
void	count_pipe_in_substr(char *substr, int *counter);
bool	end_with_quote(char *str, char quote);
void	transform_quoted_pipe(char *str, t_msh *msh);
/*==========UTILS==========*/
bool	is_space(char c);
int		customed_strlen(char *str, char charset);
#endif // !MINISHELL_H
