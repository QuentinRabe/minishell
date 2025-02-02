/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:05:54 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/30 12:27:10 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_child(void)
{
	t_msh	*msh;
	t_ppx	*pipex;

	msh = get_msh(1, NULL);
	pipex = get_pipex(1, NULL);
	if (ft_strlen_argv(msh->cmds) != 1)
	{
		close_pipe(pipex);
		cleanup_pipex(pipex);
		free_everything(msh);
	}
}

void	free_array(int **array, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_unused_pipes(t_ppx *pipex, int idx)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (i != idx - 1 && pipex->fd[i][0] >= 0)
			close(pipex->fd[i][0]);
		if (i != idx && pipex->fd[i][1] >= 0)
			close(pipex->fd[i][1]);
		i++;
	}
}

void	cleanup_pipex(t_ppx *pipex)
{
	if (pipex->nb_cmd > 1 && pipex->fd)
		free_array(pipex->fd, pipex->nb_cmd - 1);
}

int	close_pipe(t_ppx *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipex->fd[i][1] >= 0)
			close(pipex->fd[i][1]);
		if (pipex->fd[i][0] >= 0)
			close(pipex->fd[i][0]);
		i++;
	}
	return (1);
}
