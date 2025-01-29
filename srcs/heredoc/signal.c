/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:43:49 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/29 09:23:13 by arabefam         ###   ########.fr       */
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
		clean_all(msh);
		close(STDIN_FILENO);
		write(1,"\n", 1);
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
		clean_all(msh);
		close(STDIN_FILENO);
		write(1,"\n", 1);
		exit (130);
	}
}

void	reset_sig(int sig)
{
	(void) sig;
}
