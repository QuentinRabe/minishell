/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:05:54 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/03 10:17:28 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_child(void)
{
	t_msh	*msh;
	t_ppx	*data;

	msh = get_msh(1, NULL);
	data = get_data(1, NULL);
	if (ft_strlen_argv(msh->cmds) != 1)
	{
		close_pipe(data);
		cleanup_data(data);
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

void	close_unused_pipes(t_ppx *data, int idx)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		if (i != idx - 1 && data->fd[i][0] >= 0)
			close(data->fd[i][0]);
		if (i != idx && data->fd[i][1] >= 0)
			close(data->fd[i][1]);
		i++;
	}
}

void	cleanup_data(t_ppx *data)
{
	if (data->nb_cmd > 1 && data->fd)
		free_array(data->fd, data->nb_cmd - 1);
}

int	close_pipe(t_ppx *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		if (data->fd[i][1] >= 0)
			close(data->fd[i][1]);
		if (data->fd[i][0] >= 0)
			close(data->fd[i][0]);
		i++;
	}
	return (1);
}
