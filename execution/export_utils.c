/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/05 08:17:16 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_existent_key(char *key, t_var_env *env, t_var_env **prev, char *value, t_var_env **next)
{
	t_var_env	*tmp;

	while (env)
	{
		if (!ft_strcmp(env->key, key) && value)
		{
			tmp = env->next;
			free(env->key);
			free(env->value);
			free(env);
			*next = tmp;
			env = tmp;
			break ;
		}
		*prev = env;
		env = env->next;
	}
}

char	*var_value(char *str)
{
	int		index;
	char	*value;

	index = ft_strlen_set(str, '=');
	if (str[index])
		index++;
	else
		return (NULL);
	if (str[index])
	{
		value = ft_substr(str, index, ft_strlen(str + index));
		return (value);
	}
	return (NULL);
}

void	print_env(t_var_env *env, int fd)
{
	t_msh	*msh;
	bool	exp;

	exp = false;
	msh = get_msh(1, NULL);
	if (env == msh->exp)
		exp = true;
	while (env)
	{
		ft_putstr_fd(env->key, fd);
		ft_putchar_fd('=', fd);
		if (exp)
		{
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(env->value, fd);
			ft_putendl_fd("\"", fd);
		}
		else
			ft_putendl_fd(env->value, fd);
		env = env->next;
	}
}
