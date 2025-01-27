/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:33 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/27 11:52:06 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_env(t_cmd *cmds, t_var_env *env)
{
	int	fd;

	fd = 1;
	if (cmds->argv[1])
	{
		ft_putendl_fd("msh: too many arguments", 2);
		return ;
	}
	ft_redir_fd(cmds, 0, &fd);
	print_env(env, fd);
	if (fd != 1)
		close(fd);
}
