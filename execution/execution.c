/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rravelom <rravelom@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:06:08 by rravelom          #+#    #+#             */
/*   Updated: 2024/08/04 10:06:09 by rravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	child_first_process(t_cmd *ptr_cmds, t_ppx *pipex, char **env)
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
	execute(ptr_cmds, env, STDIN_FILENO, STDOUT_FILENO);
}

int	**allocate_array(int rows, int cols)
{
	int	**array;
	int	i;

	i = 0;
	array = (int **)malloc(sizeof(int *) * (rows + 1));
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
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->nb_cmd);
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

int	ft_execution(t_msh *msh, char **env)
{
	t_cmd	*ptr_cmds;
	t_ppx	pipex;
	int		status;

	ptr_cmds = msh->cmds;
	init_pipex(&pipex, msh->cmds);
	pipex.fd = create_pipe(&pipex);
	while (ptr_cmds)
	{
		pipex.pid[pipex.idx] = fork();
		if (pipex.pid[pipex.idx] == 0)
		{
			if (ft_builtins(ptr_cmds, env))
				exit(0);
			else
				child_first_process(ptr_cmds, &pipex, env);
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
