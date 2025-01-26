/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:06:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/25 23:09:58 by arabefam         ###   ########.fr       */
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
# include "../includes/minishell.h"
# include <readline/readline.h>

void	ft_exit(char **argv);
void	execute_pwd(t_cmd *cmds);
void	clear(char **command);
void	execute_cd(char **command);
void	execute_echo(t_cmd *cmds);
void	execute_export(t_msh *msh);

int		ft_builtins(t_cmd *ptr_cmd, char **env);
int		minishell(t_msh *msh, char **env);

int		ft_strlen_argv(t_cmd *cmds);
int		ft_strchr_int(char *str, char *command);
void	ft_wait(t_ppx *pipex, int *status);

int		ft_execution(t_msh *msh, char **env);

int		execute(t_cmd *ptr_cmds, char **arge, int input_fd, int output_fd);
char	*find_path(char *cmd, char **arge);

void	close_pipe(t_ppx *pipex);
void	cleanup_pipex(t_ppx *pipex);
void	free_array(int **array, int rows);
void	close_unused_pipes(t_ppx *pipex, int idx);

int		ft_error(char *msg, char *cause, int stat);

int		ft_check(char *command);
int		ft_valid_option(char **command, int *idx);
void	ft_redir_fd(t_cmd *ptr_cmds, int *input, int *output);
int		ft_herdoc(t_cmd *ptr_cmds, char **env);
void	ft_open_file(t_cmd *ptr_cmds, t_ppx *pipex, int *input, int *output);

void	ft_cmd_first(t_cmd *ptr_cmds, t_ppx *pipex, int idx, char **env);
void	ft_cmd_last(t_cmd *ptr_cmds, t_ppx *pipex, int idx, char **env);
void	ft_cmd_medium(t_cmd *ptr_cmds, t_ppx *pipex, int idx, char **env);
void	ft_cmd_one(t_cmd *ptr_cmds, char **env);

#endif
