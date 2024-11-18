/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:17 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/11 10:56:10 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <colors.h>
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
t_bool	end_with_quote(char *str, char quote);
void	transform_quoted_pipe(char *str, t_msh *msh);
t_bool	in_pipe_arr(t_msh *msh, int val);
void	restore_quoted_pipe(t_msh *msh);
void	type_token(t_msh *msh);
void	expand_vars(t_msh *msh);
/*==========ENVIRONMENT==========*/
void	create_env_lst(t_e_env **env, char **env_vars);
void	create_exp_lst(t_e_env **ex_env, char **env_vars);
void	sort_export_env(t_e_env **exp);
char	*ft_getenv(char *env, t_e_env *e_env);
/*==========UTILS==========*/
t_bool	is_space(char c);
int		customed_strlen(char *str, char charset);
void	unclosed_quote(char *cmd, char *prompt);
void	skip_space(char *str, int *i);
void	successive_pipe(char *cmd, char *prompt, t_msh *msh);
#endif // !MINISHELL_H
