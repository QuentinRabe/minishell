/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:43:49 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/06 06:43:55 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	hd_signal_handle_fake(int sig)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (sig == 2)
	{
		free_env(msh->env);
		free_env(msh->exp);
		close(msh->historic_fd);
		clean_all(msh);
		close(STDIN_FILENO);
		write(1, "\n", 1);
		exit(130);
	}
}

void	hd_signal_handle(int sig)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (sig == 2)
	{
		free_env(msh->env);
		free_env(msh->exp);
		if (msh->hd_fd_write >= 0)
		{
			close(msh->hd_fd_write);
			msh->hd_fd_write = -1;
		}
		close(msh->historic_fd);
		clean_all(msh);
		close(STDIN_FILENO);
		write(1, "\n", 1);
		exit (130);
	}
}

void	reset_sig(int sig)
{
	(void) sig;
}
