/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:33 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/04 10:46:47 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_env(t_cmd *cmds, t_var_env *env, int fd_in, int fd_out)
{
	t_ppx	*data;
	bool	std[2];

	init_stds(&std[0], &std[1]);
	data = get_data(1, NULL);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (cmds->argv[1])
	{
		ft_putendl_fd("msh: too many arguments", 2);
		child_exit_process(data, 2);
		return (1);
	}
	print_env(env, fd_out);
	if (ft_strlen_argv(cmds) == 1 && std[1])
		close(fd_out);
	child_exit_process(data, 2);
	return (1);
}
