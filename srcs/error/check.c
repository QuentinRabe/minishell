/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:20:30 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/12 07:21:53 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unclosed_quote(char *cmd, char *prompt)
{
	int		i;
	char	quote;
	bool	result;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			quote = cmd[i];
			result = false;
			while (cmd[++i])
			{
				if (cmd[i] == quote)
				{
					result = true;
					break;
				}
			}
			if (!result)
			{
				free(prompt);
				free(cmd);
				exit(1);
			}
		}
	}
}