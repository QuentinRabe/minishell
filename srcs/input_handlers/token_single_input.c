/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_single_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:24:27 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/10 09:32:00 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	***create_token_single_cmd(t_msh *msh, char *input)
{
	char	**splitted;
	char	***result;

	msh->cmds = (t_cmd *) malloc(sizeof(t_cmd));
	if (!msh->cmds)
		return (NULL);
	msh->cmds->value = input;
	splitted = split_single_input(input);
	free(input);
	msh->cmds->token_lis = create_token_list(splitted);
	msh->cmds->next = NULL;
	result = (char ***) malloc(sizeof(char **) * 2);
	if (!result)
		return (NULL);
	result[0] = splitted;
	result[1] = NULL;
	return (result);
}
