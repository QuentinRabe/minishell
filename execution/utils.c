/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:46:46 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/27 14:25:50 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strlen_argv(t_cmd *cmds)
{
	t_cmd	*ptr_cmd;
	int		i;

	i = 0;
	ptr_cmd = cmds;
	while (ptr_cmd)
	{
		if (ptr_cmd->argv[0])
			i++;
		ptr_cmd = ptr_cmd->next;
	}
	return (i);
}

void	ft_wait(t_ppx *pipex, int *status)
{
	int	i;

	i = 0;
	waitpid(pipex->pid, status, 0);
	while (i < pipex->nb_cmd)
	{
		wait(NULL);
		i++;
	}
}
