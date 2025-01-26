/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rravelom <rravelom@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:05:54 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/18 10:05:55 by rravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->nb_cmd != 1 && pipex->fd)
		free_array(pipex->fd, pipex->nb_cmd - 1);
}

void	close_pipe(t_ppx *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		close(pipex->fd[i][1]);
		close(pipex->fd[i][0]);
		i++;
	}
}
