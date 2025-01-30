/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:46:46 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/30 12:32:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_child(void)
{
	t_msh	*msh;
	t_ppx	*pipex;

	msh = get_msh(1, NULL);
	pipex = get_pipex(1, NULL);
	cleanup_pipex(pipex);
	free_everything(msh);
}

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
	int		i;
	t_msh	*msh;

	i = 0;
	msh = get_msh(1, NULL);
	waitpid(pipex->pid, status, 0);
	msh->status = (*status >> 8) & 0xFF;
	while (i < pipex->nb_cmd)
	{
		wait(NULL);
		i++;
	}
}

bool	is_only(char *set, char *str)
{
	int		i;
	int		j;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	if (count == ft_strlen(str))
		return (true);
	else
		return (false);
}
