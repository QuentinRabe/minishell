/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:17 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/07 13:35:27 by arabefam         ###   ########.fr       */
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
# include <string.h>

// ==============EXPANSION==============
void	expand_variables(t_type type, t_cmd *cmds, t_var_env *env);
// ==============ENVIRONMENT==============
void	get_var_env(t_var_env **env, char **args);
void	sort_list_env(t_var_env **env);
char	*get_env(t_var_env *env, char *key);
// ==============INPUT_HANDLERS==============
bool	has_obvious_syntax_error(char *str);
bool	has_too_much_arrows(char *str);
bool	has_consecutive_opps_arrows(char *str);
bool	has_redir_without_filname(char *str);
char	**split_single_input(char *str);
char	**split_multi_input(char *str);
bool	has_pipe(char *str);
int		count_additionnal_spaces(char *str);
void	format_input(char **str);
// ==============TOKEN==============
char	***create_token_single_cmd(t_msh *msh, char *input);
char	***create_token_multi_cmds(t_msh *msh, char *input);
t_token	*create_token_list(char **tokens);
// ==============UTILS==============
bool	is_space(char c);
bool	is_in(char *set, char c, int *index);
void	trim(char **str);
char	**ft_split_set(char *s, char *set);
void	print_list(t_cmd *head);
int		count_additionnal_spaces(char *str);
void	free_argv(char **argv);
#endif // !MINISHELL_H
