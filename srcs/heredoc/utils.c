/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:34:32 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/19 08:34:40 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_there_heredoc(t_redir *list)
{
	while (list)
	{
		if (list->type == HEREDOC)
			return (true);
		list = list->next;
	}
	return (false);
}
