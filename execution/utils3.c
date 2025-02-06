/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:00:02 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/06 08:45:43 by arabefam         ###   ########.fr       */
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
	t_msh	*msh;

	msh = get_msh(1, NULL);
	redir = ptr_cmd->redir_list;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->is_last)
		{
			if (redir->heredoc_fd[0] >= 0)
			{
				close(redir->heredoc_fd[0]);
				msh->hd_fd_write = -1;
			}
			if (redir->heredoc_fd[1] >= 0)
				close(redir->heredoc_fd[1]);
		}
		redir = redir->next;
	}
}
