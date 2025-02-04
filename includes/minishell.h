/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:17 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/04 11:15:38 by arabefam         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <data.h>
# include <messages.h>
# include <../execution/header.h>
# include <../srcs/gnl/get_next_line.h>

void	expand_variables(t_type type, t_cmd *cmds, t_var_env *env);
void	expand_input(char **input, t_var_env *env);
char	*get_varname(char *token, int i);
int		get_varlen(char *token);
int		get_len_new_token(char *token, t_var *list);
int		get_varlen_hd(char *token);
char	*get_varname_hd(char *token, int i);
int		get_len_new_input_hd(char *input, t_var *list);
size_t	get_splitted_lenght(char **splitted, int *spaces);
void	check_filename_in_dq(char *token, t_token *curr);
void	create_new_value(char *new, char **splitted);
void	one_espace_value(char *value, t_var *new);
void	increment(char *token, int *i);
void	init_array(int i[3]);
void	get_var_env(t_var_env **env, char **args);
void	sort_list_env(t_var_env **env);
char	*get_env(t_var_env *env, char *key);
char	**get_env_arr(t_var_env *env);
bool	has_obvious_syntax_error(char *str);
bool	has_too_much_arrows(char *str);
bool	has_consecutive_opps_arrows(char *str);
bool	has_redir_without_filname(char *str);
char	**split_single_input(char *str);
char	**split_multi_input(char *str);
bool	has_pipe(char *str);
int		count_additionnal_spaces(char *str);
void	format_input(char **str);
void	create_token_single_cmd(t_msh *msh, char *input);
void	create_token_multi_cmds(t_msh *msh, char *input);
t_token	*create_token_list(char **tokens);
bool	is_space(char c);
bool	is_in(char *set, char c, int *index);
bool	is_in_quotes(char *token, int i, char quote);
void	trim(char **str);
char	**ft_split_set(char *s, char *set);
void	print_list(t_cmd *head);
void	print_argv(t_cmd *head);
int		count_additionnal_spaces(char *str);
void	free_argv(char **argv);
void	free_var_list(t_var *head);
bool	is_in_sq(char *token, int i);
bool	is_in_dq(char *token, int i);
void	clean_all(t_msh *msh);
void	free_env(t_var_env *env);
bool	count_if_quote_case(char *token, int *count);
void	free_everything(t_msh *msh);
void	init_signal(void);
void	signal_handler(int sig);
void	free_tokens(t_token *head);
void	free_redir_list(t_redir *head);
void	free_cmds(t_cmd *head);
void	free_msh(t_msh *msh);
t_msh	*get_msh(int i, t_msh *msh);
char	**get_arr(int i, char **arr);
bool	is_only(char *set, char *str);
t_msh	*get_msh(int i, t_msh *msh);
int		check_heredoc(t_msh	*msh);
bool	is_there_heredoc(t_redir *list);
void	reset_sig(int sig);
void	hd_signal_handle(int sig);
void	hd_signal_handle_fake(int sig);
void	fake_redoc_process(char *eof, t_msh *msh);
void	build_argv(t_msh *msh);
void	remove_quotes(t_msh *msh);
void	build_redir_list(t_msh *msh);
int		count_redir(t_token *token_list);
int		heredoc_delimiter_len(char *str);
void	check_last_redir(t_redir *list);
void	create_delimiter(char *new, char *old);
#endif
