/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:43:49 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/28 13:31:21 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	hd_signal_handle_fake(int sig)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (sig == 2)
	{
		msh->status = sig + 128;
		free_env(msh->env);
		free_env(msh->exp);
		clean_all(msh);
		write(1,"\n", 1);
		close(STDIN_FILENO);
		exit(msh->status);
	}
}

void	hd_signal_handle(int sig)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (sig == 2)
	{
		msh->status = sig + 128;
		free_env(msh->env);
		free_env(msh->exp);
		clean_all(msh);
		close(STDIN_FILENO);
		write(1,"\n", 1);
		exit (msh->status);
	}
}

void	reset_sig(int sig)
{
	(void) sig;
}
