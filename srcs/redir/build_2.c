/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:28:02 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/23 16:31:03 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_delimiter(char *new, char *old)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '\'' || old[i] == '"')
		{
			quote = old[i];
			i++;
			while (old[i] && old[i] != quote)
				new[j++] = old[i++];
			if (old[i])
				i++;
		}
		else
			new[j++] = old[i++];
	}
	new[j] = '\0';
}
