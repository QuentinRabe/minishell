/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:24:11 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/28 09:33:04 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_var(t_var_env *env, char *key)
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
			break ;
		}
		prev = env;
		env = env->next;
	}
}

static void	unset_process(char **argv, t_var_env *env)
{
	int			i;

	i = 0;
	while (argv[++i])
		remove_var(env, argv[i]);
}

void	execute_unset(t_cmd *cmds)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (!cmds->argv[1])
		ft_error("not enough arguments", NULL, 1);
	else
		unset_process(cmds->argv, msh->env);
}
