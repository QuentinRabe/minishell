/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:20:30 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/01 11:51:55 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	successive_pipe(char *cmd, t_msh *msh)
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
				ft_putstr_fd("Token error near |\n", 2);
				msh->ex_status = 2;
				return (FALSE);
			}
		}
		else
			i++;
	}
	return (TRUE);
}

t_bool	unclosed_quote(char *cmd, t_msh *msh)
{
	int		i;
	char	quote;
	t_bool	result;

	i = -1;
	result = TRUE;
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
					break ;
				}
			}
			if (!result)
			{
				msh->ex_status = 2;
				return (FALSE);
			}
		}
	}
	return (result);
}
