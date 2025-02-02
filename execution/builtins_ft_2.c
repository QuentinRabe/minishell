/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:33 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/30 13:34:44 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_env(t_cmd *cmds, t_var_env *env)
{
	int		fd;
	t_ppx	*pipex;

	fd = 1;
	pipex = get_pipex(1, NULL);
	if (cmds->argv[1])
	{
		ft_putendl_fd("msh: too many arguments", 2);
		child_exit_process(pipex, 2);
		return (1);
	}
	ft_redir_out(cmds, &fd);
	print_env(env, fd);
	if (fd != 1)
		close(fd);
	child_exit_process(pipex, 2);
	return (1);
}
