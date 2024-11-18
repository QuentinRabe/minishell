/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:26:42 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/18 08:26:42 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_getenv(char *env, t_e_env *e_env)
{
	while (e_env)
	{
		if (!ft_strcmp(env, e_env->key))
			return (e_env->value);
		e_env = e_env->next;
	}
	return (NULL);
}
