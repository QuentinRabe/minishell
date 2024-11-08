/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:17:56 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 11:06:54 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	free_tokens()

// void	free_msh(t_msh *msh)
// {

// }

void	print_tokens(t_token *token, int cmd_id, int token_id)
{
	printf("From cmd [%d] --> Token [%d] is %s\n", cmd_id, token_id, token->value);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
