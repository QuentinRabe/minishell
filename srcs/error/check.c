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

void	successive_pipe(char *cmd, char *prompt, t_msh *msh)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			skip_space(cmd, &i);
			if (cmd[i] == '|')
			{
				free(msh->pipe_pos);
				free(prompt);
				free(cmd);
				exit(1);
			}
		}
		else
			i++;
	}
}

void	unclosed_quote(char *cmd, char *prompt)
{
	int		i;
	char	quote;
	t_bool	result;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			quote = cmd[i];
			result = FALSE;
			while (cmd[++i])
			{
				if (cmd[i] == quote)
				{
					result = TRUE;
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