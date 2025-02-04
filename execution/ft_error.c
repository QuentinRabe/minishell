/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:03:31 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/04 08:29:57 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_error(char *msg, char *cause, int stat)
{
	int		size;
	int		len;
	t_ppx	*data;
	t_msh	*msh;

	msh = get_msh(1, NULL);
	len = ft_strlen(cause);
	size = ft_strlen(msg);
	write (2, "msh: ", 5);
	write (2, msg, size);
	if (cause != NULL)
		write (2, cause, len);
	write (2, "\n", 2);
	data = get_data(1, NULL);
	if (ft_strlen_argv(msh->cmds) != 1)
	{
		close_pipe(data);
		cleanup_data(data);
	}
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

t_ppx	*get_data(int i, t_ppx *data)
{
	static t_ppx	*ptr;

	if (i == 0)
		ptr = data;
	return (ptr);
}
