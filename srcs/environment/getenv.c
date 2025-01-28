/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:45:29 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/28 08:30:56 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(t_var_env *env, char *key)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(msh->status));
	if (!ft_strcmp(key, "\"")
		|| !ft_strcmp(key, "'"))
		return (ft_strjoin("$", key));
	if (!ft_strcmp(key, "$"))
		return (ft_strdup("ID"));
	if (key[0] == '\0')
		return (ft_strdup("$"));
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
