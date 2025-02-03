/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:06:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/03 14:04:01 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../includes/minishell.h"
# include <readline/readline.h>

int		ft_exit(char **argv, int fd);
int		execute_pwd(t_cmd *cmds, int fd);
int		execute_cd(char **command);
int		execute_echo(t_cmd *cmds, int fd);
int		execute_export(t_cmd *cmd, int fd);

int		ft_builtins(t_msh *msh, t_cmd *ptr_cmd, char **env, int fd);
int		minishell(t_msh *msh, char **env);

int		ft_strlen_argv(t_cmd *cmds);
void	ft_wait(t_ppx *data, int *status);

int		ft_execution(t_msh *msh, char **env);

int		execute(t_cmd *ptr_cmds, char **arge);
char	*find_path(char *cmd, char **arge);

int		close_pipe(t_ppx *data);
void	cleanup_data(t_ppx *data);
void	free_array(int **array, int rows);
void	close_unused_pipes(t_ppx *data, int idx);

int		ft_error(char *msg, char *cause, int stat);
void	sig_handle(int sig);
void	config_sig(void);
t_ppx	*get_data(int i, t_ppx *data);

int		ft_check(char *command);
int		ft_valid_option(char **command, int *idx);
void	ft_redir_in(t_cmd *ptr_cmd, int *input);
void	ft_redir_out(t_cmd *ptr_cmd, int *output);
int		ft_herdoc(t_cmd *ptr_cmds, char **env);
void	ft_open_file(t_cmd *ptr_cmds, t_ppx *data, int *input, int *output);

void	print_env(t_var_env *env, int fd);
int		execute_env(t_cmd *cmds, t_var_env *env);
int		execute_unset(t_cmd *cmds);
t_ppx	*get_data(int i, t_ppx *data);
void	free_child(void);
void	child_exit_process(t_ppx *data, int status);
int		remove_var_exp(t_var_env *env, char *key, char *value);
bool	export_valid_varname(char *name);
void	sort_new_exp(t_var_env *exp);
void	close_heredoc_fd(t_cmd *ptr_cmd);
void	print_env(t_var_env *env, int fd);
char	*var_value(char *str);
void	free_existent_key(char *key, t_var_env *env, t_var_env **prev);
#endif
