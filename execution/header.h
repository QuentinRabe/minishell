/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:06:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/06 09:06:21 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../includes/minishell.h"
# include <readline/readline.h>

int			ft_exit(char **argv, int fd_in, int fd_out);
int			execute_pwd(t_cmd *cmds, int fd_in, int fd_out);
int			execute_cd(char **command, int fd_in, int fd_out);
int			execute_echo(t_cmd *cmds, int fd_in, int fd_out);
int			execute_export(t_cmd *cmd, int fd_in, int fd_out);

int			ft_builtins(t_msh *msh, t_cmd *ptr_cmd, char **env, int fd);
int			minishell(t_msh *msh, char **env);
int			is_builtins(void);

int			ft_strlen_argv(t_cmd *cmds);
void		ft_wait(t_ppx *data, int *status);

int			ft_execution(t_msh *msh, char **env);

int			execute(t_cmd *ptr_cmds, char **arge);
char		*find_path(char *cmd, char **arge);

int			close_pipe(t_ppx *data);
void		cleanup_data(t_ppx *data);
void		free_array(int **array, int rows);
void		close_unused_pipes(t_ppx *data, int idx);

int			ft_error(char *msg, char *cause, int stat);
void		sig_handle(int sig);
void		config_sig(void);
t_ppx		*get_data(int i, t_ppx *data);

int			ft_check(char *command);
int			ft_valid_option(char **command, int *idx);
void		ft_redir_in(t_cmd *ptr_cmd, int *input, bool *std);
void		ft_redir_out(t_cmd *ptr_cmd, int *output, bool *std);
int			ft_herdoc(t_cmd *ptr_cmds, char **env);
void		ft_open_file(t_cmd *ptr_cmds, t_ppx *data, int *input, int *output);

void		print_env(t_var_env *env, int fd);
int			execute_env(t_cmd *cmds, t_var_env *env, int fd_in, int fd_out);
int			execute_unset(t_cmd *cmds, int fd_in, int fd_out);
t_ppx		*get_data(int i, t_ppx *data);
void		free_child(void);
void		child_exit_process(t_ppx *data, int status);
int			remove_var_exp(t_var_env *env, char *key, char *value);
bool		export_valid_varname(char *name);
void		sort_new_exp(t_var_env *exp);
void		close_heredoc_fd(t_cmd *ptr_cmd);
void		print_env(t_var_env *env, int fd);
char		*var_value(char *str);
t_var_env	*free_existent_key(char *key, t_var_env *env, \
t_var_env **prev, char *value);
int			exit_process(char *arg1, char *arg2, t_ppx *data, t_msh *msh);
int			is_directory(const char *path);
int			check_absolute_path(char *path, char **cmd);
char		*get_cmd(char *path);
void		init_stds(bool *std_in, bool *std_out);
int			check_fd(int *fd_in, int *fd_out, bool *std_in, bool *std_out);
void		add_new_env(t_var_env *env, char *key, char *value);
void		free_and_error_path(char *path, char *msg, char *cmd, int stat);
int			change_dir(char *dir, t_msh *msh, t_ppx *data);
t_cmd		*get_ptr_cmd(int i, t_cmd *cmd);
#endif
