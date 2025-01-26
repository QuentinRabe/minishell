/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:46:46 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/25 22:55:32 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	space_chr(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr_int(char *str, char *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = space_chr(str);
	while (str[i] == command[j] && str[i] != '\0' && command[j] != '\0')
	{
		i++;
		j++;
	}
	if (command[j] == '\0')
	{
		if (str[i] != '\0' && str[i] != ' ')
			return (0);
		else
			return (1);
	}
	return (0);
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
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		waitpid(pipex->pid[i], status, 0);
		i++;
	}
}
