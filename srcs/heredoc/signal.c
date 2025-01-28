/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:43:49 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/28 09:01:01 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	hd_signal_handle(int sig)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (sig == 2)
	{
		close(1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		msh->status = sig + 128;
		free_everything(msh);
		exit (msh->status);
	}
}

void	reset_sig(int sig)
{
	(void) sig;
}
