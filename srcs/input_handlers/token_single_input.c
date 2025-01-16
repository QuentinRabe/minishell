/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_single_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:24:27 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/16 09:02:05 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_token_single_cmd(t_msh *msh, char *input)
{
	char	**splitted;

	msh->cmds = (t_cmd *) malloc(sizeof(t_cmd));
	if (!msh->cmds)
		return ;
	msh->cmds->value = ft_strdup(input);
	msh->cmds->argv = NULL;
	splitted = split_single_input(input);
	free(input);
	msh->cmds->token_lis = create_token_list(splitted);
	msh->cmds->next = NULL;
	free_argv(splitted);
}
