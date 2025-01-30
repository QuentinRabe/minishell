/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:06:08 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/30 12:48:09 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	child_first_process(t_msh *msh, t_cmd *ptr_cmds, t_ppx *pipex, char **env)
{
	int	input;
	int	output;

	input = -1;
	output = -1;
	ft_open_file(ptr_cmds, pipex, &input, &output);
	if (pipex->nb_cmd > 1 && pipex->idx > 0)
		dup2(pipex->fd[pipex->idx - 1][0], STDIN_FILENO);
	if (pipex->nb_cmd > 1 && pipex->idx < pipex->nb_cmd - 1)
		dup2(pipex->fd[pipex->idx][1], STDOUT_FILENO);
	if (pipex->idx == 0)
		dup2(input, STDIN_FILENO);
	if (pipex->idx == pipex->nb_cmd - 1)
		dup2(output, STDOUT_FILENO);
	if (input >= 0)
		close(input);
	if (output >= 0)
		close(output);
	close_unused_pipes(pipex, pipex->idx);
	if (ft_builtins(msh, ptr_cmds, env, STDOUT_FILENO))
	{
		close_pipe(pipex);
		return ;
	}
	execute(ptr_cmds, env);
}

int	**allocate_array(int rows, int cols)
{
	int	**array;
	int	i;

	i = 0;
	array = (int **)malloc(sizeof(int *) * rows + 1);
	if (array == NULL)
	{
		perror("Erreur d'allocation pour les lignes");
		return (NULL);
	}
	while (i < rows)
	{
		array[i] = (int *)malloc(sizeof(int) * cols);
		if (array[i] == NULL)
		{
			while (i > 0)
				free(array[i--]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}

void	init_pipex(t_ppx *pipex, t_cmd	*cmds)
{
	pipex->idx = 0;
	pipex->nb_cmd = ft_strlen_argv(cmds);
	if (pipex->nb_cmd > 1)
	{
		pipex->fd = allocate_array(pipex->nb_cmd - 1, 2);
		if (pipex->fd == NULL)
			exit(1);
	}
}

int	**create_pipe(t_ppx *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->fd[i]) == -1)
			perror("pipe");
		i++;
	}
	return (pipex->fd);
}
void	sig_handle(int sig)
{
	(void) sig;
}


void	config_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

t_ppx	*get_pipex(int i, t_ppx *pipex)
{
	static t_ppx	*ptr;

	if (i == 0)
		ptr = pipex;
	return (ptr);
}

int	ft_execution(t_msh *msh, char **env)
{
	t_cmd	*ptr_cmds;
	t_ppx	pipex;
	int		status;

	get_pipex(0, &pipex);
	ptr_cmds = msh->cmds;
	init_pipex(&pipex, msh->cmds);
	pipex.fd = create_pipe(&pipex);
	signal(SIGINT, sig_handle);
	while (ptr_cmds)
	{
		pipex.pid/*[pipex.idx]*/ = fork();
		if (pipex.pid/*[pipex.idx]*/ == 0)
		{
			config_sig();
			child_first_process(msh, ptr_cmds, &pipex, env);
			exit(0);
		}
		pipex.idx++;
		ptr_cmds = ptr_cmds->next;
	}
	close_pipe(&pipex);
	ft_wait(&pipex, &status);
	cleanup_pipex(&pipex);
	return (1);
}
