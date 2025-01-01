/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:34:08 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/01 12:14:38 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	restore_quoted_pipe(t_msh *msh)
{
	int		i;
	t_cmd	*curr_cmd;

	curr_cmd = msh->cmd_lst;
	while (curr_cmd)
	{
		i = -1;
		while (curr_cmd->value[++i])
		{
			if (in_pipe_arr(msh, msh->i_qut_pipe))
				curr_cmd->value[i] = '|';
			msh->i_qut_pipe += 1;
		}
		msh->i_qut_pipe += 1;
		curr_cmd = curr_cmd->next;
	}
}

static void	check_for_quoted_pipe(char *str, int *i, int *j, int *pos)
{
	char	quote;
	int		result;

	if (str[*i] && str[*i + 1] && (str[*i] == '\'' || str[*i] == '"'))
	{
		quote = str[*i];
		result = end_with_quote(&str[*i + 1], quote);
		if (result == TRUE)
		{
			*i += 1;
			while (str[*i] && str[*i] != quote)
			{
				if (str[*i] == '|')
				{
					pos[*j] = *i;
					*j += 1;
					str[*i] = '@';
				}
				*i += 1;
			}
			if (str[*i + 1])
				*i += 1;
		}
	}
}

void	transform_quoted_pipe(char *str, t_msh *msh)
{
	int		i;
	int		j;

	msh->quoted_pipe = count_quoted_pipe(str);
	msh->pipe_pos = (int *) malloc(msh->quoted_pipe * sizeof(int));
	if (!msh->pipe_pos)
		return ;
	i = 0;
	j = 0;
	while (str[++i])
		check_for_quoted_pipe(str, &i, &j, msh->pipe_pos);
}
