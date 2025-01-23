/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:30:34 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/23 16:01:12 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_in_quotes(char *token, int i, char quote)
{
	int		tmp;
	int		count;

	tmp = i;
	count = 0;
	while (i >= 0)
	{
		if (token[i] && token[i] == quote)
		{
			count++;
			break ;
		}
		i--;
	}
	i = tmp;
	while (token[i])
	{
		if (token[i] == quote)
		{
			count++;
			break;
		}
		i++;
	}
	return (count == 2);
}

bool	is_in_dq(char *token, int i)
{
	return is_in_quotes(token, i, '"');
}

bool	is_in_sq(char *token, int i)
{
	return is_in_quotes(token, i, '\'');
}

void	free_everything(t_msh *msh)
{
	free_env(msh->env);
	free_env(msh->exp);
	clean_all(msh);
}

void	print_argv(t_cmd *head)
{
	t_cmd	*ptr_cmd;
	int		i;

	ptr_cmd = head;
	while (ptr_cmd)
	{
		i = -1;
		printf("Argv -> ");
		while (ptr_cmd->argv[++i])
			printf("[%s]", ptr_cmd->argv[i]);
		printf("\n");
		ptr_cmd = ptr_cmd->next;
	}
}

void	print_list(t_cmd *head)
{
	t_cmd	*ptr_cmd;
	t_redir	*ptr_redir;

	ptr_cmd = head;
	while (ptr_cmd)
	{
		ptr_redir = ptr_cmd->redir_list;
		while (ptr_redir)
		{
			printf("[%s][%d]", ptr_redir->filename, ptr_redir->expand);
			ptr_redir = ptr_redir->next;
		}
		printf("\n");
		ptr_cmd = ptr_cmd->next;
	}
}

bool	is_in(char *set, char c, int *index)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (c == set[i])
		{
			if (index)
				*index = i;
			return (true);
		}
	}
	return (false);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
