/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mutli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:13:03 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/05 13:22:47 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	restore(char *str)
{
	while (*str)
	{
		if (*str == -1)
			*str = '|';
		str++;
	}
}

static void	substitute_pipes(char *str, char delimiter)
{
	while (*str && *str != delimiter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimiter)
	{
		if (is_in("|", *str, NULL))
			*str = -1;
		str++;
	}
	if (*str)
	{
		str++;
		substitute_pipes(str, delimiter);
	}
}

char	**split_multi_input(char *str)
{
	char	**splitted;
	char	**ptr;

	substitute_pipes(str, '"');
	substitute_pipes(str, '\'');
	splitted = ft_split(str, '|');
	ptr = splitted;
	while (*ptr)
	{
		restore(*ptr);
		ptr++;
	}
	return (splitted);
}
