/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:24:11 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/04 10:53:14 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	remove_var(t_var_env *env, char *key)
{
	t_var_env	*tmp;
	t_var_env	*prev;

	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			tmp = env->next;
			free(env->key);
			free(env->value);
			free(env);
			prev->next = tmp;
			env = tmp;
			return (1);
		}
		prev = env;
		env = env->next;
	}
	return (0);
}

static void	unset_process(char **argv, t_var_env *env)
{
	int			i;
	t_msh		*msh;

	i = 0;
	msh = get_msh(1, NULL);
	while (argv[++i])
	{
		remove_var(env, argv[i]);
		remove_var(msh->exp, argv[i]);
	}
}

int	execute_unset(t_cmd *cmds, int fd_in, int fd_out)
{
	t_msh	*msh;
	t_ppx	*data;
	bool	std[2];

	init_stds(&std[0], &std[1]);
	msh = get_msh(1, NULL);
	data = get_data(1, NULL);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (ft_strlen_argv(cmds) == 1 && std[1])
		close(fd_out);
	if (!cmds->argv[1])
	{
		ft_putendl_fd("msh: not enough arguments", 2);
		child_exit_process(data, 1);
		return (1);
	}
	else
		unset_process(cmds->argv, msh->env);
	child_exit_process(data, 0);
	return (0);
}
