/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:24:11 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/02 09:46:49 by arabefam         ###   ########.fr       */
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

int	execute_unset(t_cmd *cmds)
{
	t_msh	*msh;
	t_ppx	*pipex;

	pipex = get_pipex(1, NULL);
	msh = get_msh(1, NULL);
	if (!cmds->argv[1])
	{
		ft_putendl_fd("msh: not enough arguments", 2);
		child_exit_process(pipex, 1);
		return (1);
	}
	else
		unset_process(cmds->argv, msh->env);
	child_exit_process(pipex, 0);
	return (0);
}
