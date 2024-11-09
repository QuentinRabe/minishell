/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:45:22 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 15:40:09 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd	*find_last_cmd(t_cmd *cmd_lst)
{
	if (cmd_lst == NULL)
		return (NULL);
	while (cmd_lst->next)
		cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

static void	add_cmd(char *cmd, t_cmd **cmd_lst)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	new_cmd = (t_cmd *) malloc(sizeof(t_cmd));
	//free if failed
	new_cmd->value = ft_strdup(ft_strtrim(cmd, " "));
	new_cmd->next = NULL;
	if (*cmd_lst == NULL)
		*cmd_lst = new_cmd;
	else
	{
		last_cmd = find_last_cmd(*cmd_lst);
		last_cmd->next = new_cmd;
	}
}

void	create_cmd_lst(char *input, t_msh *msh)
{
	char	**splitted;
	char	**ptr;
	// t_cmd	*current;
	int		i;

	(void) msh;
	splitted = ft_split(input, '|');
	ptr = splitted;
	while (*ptr)
	{
		add_cmd(*ptr, &msh->cmd_lst);
		ptr++;
	}
	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
	// while (msh->cmd_lst)
	// {
	// 	current = msh->cmd_lst->next;
	// 	free(msh->cmd_lst->value);
	// 	free(msh->cmd_lst);
	// 	msh->cmd_lst = current;
	// }
	// msh->cmd_lst = NULL;
}
