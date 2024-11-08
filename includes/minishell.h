/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:17 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 10:48:16 by arabefam         ###   ########.fr       */
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

bool	is_space(char c);
void	init_tokenization(char *str, t_cmd *cmd_arr);
void	skip_space(char *str, int *index);
int 	count_tokens(char *str);
int		count_cmds(char **array);
int		customed_strlen(char *str, char charset);
void	create_tokens(t_token *tokens, char *str);
void	print_tokens(t_token *token, int cmd_id, int token_id);
char	*get_prompt_cwd(void);
char	**extract_path_from_env(char **env);
#endif // !MINISHELL_H
