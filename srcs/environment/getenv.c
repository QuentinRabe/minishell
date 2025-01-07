/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:45:29 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/07 09:03:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(t_var_env *env, char *key)
{
	if (!ft_strcmp(key, "?"))
		return ("0");
	while (env)
	{
		if (env->key == key)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
