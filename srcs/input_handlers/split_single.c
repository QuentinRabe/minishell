/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:27:06 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/06 21:16:30 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	restore(char *str)
{
	while (*str)
	{
		if (*str <= -1 && *str >= -6)
			*str = SPACES[((int)(*str) + 1) * -1];
		str++;
	}
}

static void	substitute_spaces(char *str, char delimiter)
{
	char	*ptr;
	int		i;

	i = 0;
	while (*str && *str != delimiter)
		str++;
	if (*str)
		str++;
	ptr = str;
	while (*ptr && *ptr != delimiter)
		ptr++;
	if (*ptr == '\0')
		return ;
	while (*str && *str != delimiter)
	{
		if (is_in(SPACES, *str, &i))
			*str = (i + 1) * -1;
		str++;
	}
	if (*str)
	{
		str++;
		substitute_spaces(str, delimiter);
	}
}

char	**split_single_input(char *str)
{
	char	**splitted;
	char	**ptr;

	substitute_spaces(str, '"');
	substitute_spaces(str, '\'');
	splitted = ft_split_set(str, SPACES);
	ptr = splitted;
	while (*ptr)
	{
		restore(*ptr);
		ptr++;
	}
	return (splitted);
}
