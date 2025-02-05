/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:40:37 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/05 08:51:33 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_env(t_msh *msh, char *dir)
{
	add_new_env(msh->exp, "PWD", dir);
	add_new_env(msh->env, "PWD", dir);
}

int	change_dir(char *dir, t_msh *msh, t_ppx *data)
{
	char	cwd[1024];

	if (!dir || !ft_strcmp(dir, "~"))
	{
		dir = get_env(msh->exp, "HOME");
		chdir(dir);
		update_env(msh, dir);
		free(dir);
		return (child_exit_process(data, 0), 0);
	}
	else if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(dir, 2);
		return (child_exit_process(data, 1), 1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env(msh, cwd);
	return (child_exit_process(data, 0), 0);
}
