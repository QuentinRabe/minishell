/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:33 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/04 08:13:26 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_env(t_cmd *cmds, t_var_env *env)
{
	int		fd;
	t_ppx	*data;
	bool	std;

	std = false;
	fd = 1;
	data = get_data(1, NULL);
	if (cmds->argv[1])
	{
		ft_putendl_fd("msh: too many arguments", 2);
		child_exit_process(data, 2);
		return (1);
	}
	ft_redir_out(cmds, &fd, &std);
	print_env(env, fd);
	if (ft_strlen_argv(cmds) == 1 && std)
		close(fd);
	child_exit_process(data, 2);
	return (1);
}
