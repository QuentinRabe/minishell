/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:03:31 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/29 10:41:55 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_error(char *msg, char *cause, int stat)
{
	int		size;
	int		len;
	t_ppx	*pipex;

	len = ft_strlen(cause);
	size = ft_strlen(msg);
	write (2, "msh: ", 5);
	write (2, msg, size);
	if (cause != NULL)
		write (2, cause, len);
	write (2, "\n", 2);
	pipex = get_pipex(1, NULL);
	close_pipe(pipex);
	cleanup_pipex(pipex);
	free_everything(get_msh(1, NULL));
	exit (stat);
}

void	sig_handle(int sig)
{
	(void) sig;
}

void	config_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

t_ppx	*get_pipex(int i, t_ppx *pipex)
{
	static t_ppx	*ptr;

	if (i == 0)
		ptr = pipex;
	return (ptr);
}
