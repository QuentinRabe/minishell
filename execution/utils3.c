/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:00:02 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/05 18:21:03 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_stds(bool *std_in, bool *std_out)
{
	*std_in = false;
	*std_out = false;
}

void	close_heredoc_fd(t_cmd *ptr_cmd)
{
	t_redir	*redir;

	redir = ptr_cmd->redir_list;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->is_last)
		{
			if (redir->heredoc_fd[0] >= 0)
				close(redir->heredoc_fd[0]);
			if (redir->heredoc_fd[1] >= 0)
				close(redir->heredoc_fd[1]);
		}
		redir = redir->next;
	}
}
