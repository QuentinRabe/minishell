/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 08:56:18 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/03 07:09:47 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	sort_new_exp(t_var_env *exp)
{
	while (exp && !exp->is_new)
		exp = exp->next;
	if (exp)
		sort_list_env(&exp);
}

bool	export_valid_varname(char *name)
{
	int	i;

	i = 1;
	while (name[i])
	{
		if(!ft_isalnum(name[i]))
			return (false);
		i++;
	}
	return (true);
}

int	remove_var_exp(t_var_env *env, char *key, char *value)
{
	t_var_env	*tmp;
	t_var_env	*prev;

	while (env)
	{
		if (!ft_strcmp(env->key, key) && value)
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
