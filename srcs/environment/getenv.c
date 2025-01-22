/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:45:29 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/22 13:48:35 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(t_var_env *env, char *key)
{
	char	spec;

	spec = -1;
	if (is_in("\"'", key[0], NULL)
		&& is_in("\"'", key[ft_strlen(key) - 1], NULL))
		return (ft_strdup(key));
	if (!ft_strcmp(key, "?"))
		return (ft_strdup("0"));
	if (!ft_strcmp(key, &spec))
		return (ft_strdup("$"));
	if (!ft_strcmp(key, "$"))
		return (ft_strdup("ID"));
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
