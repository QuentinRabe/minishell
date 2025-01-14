/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_single_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:24:27 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/14 09:26:35 by arabefam         ###   ########.fr       */
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
	splitted = split_single_input(input);
	free(input);
	msh->cmds->token_lis = create_token_list(splitted);
	msh->cmds->next = NULL;
	free_argv(splitted);
}
