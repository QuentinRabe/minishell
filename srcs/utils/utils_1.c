/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:22:54 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/01 12:25:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reset(t_msh *msh)
{
	free(msh->pipe_pos);
	free(msh->cmd);
}

void	skip_space(char *str, int *i)
{
	while (str[*i] && is_space(str[*i]))
		*i += 1;
}

int	customed_strlen(char *str, char charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] != charset)
	{
		i++;
		counter++;
	}
	return (counter);
}

t_bool	is_space(char c)
{
	return (c == ' ');
}
