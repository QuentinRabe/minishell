/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:54:26 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/26 12:38:29 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_new_env(t_var_env *env, char *key, char *value)
{
	t_var_env	*tmp;
	t_var_env	*new;

	while (env->next)
	{
		printf("Comparating [%s][%s]\n", env->key, key);
		if (!ft_strcmp(env->key, key))
		{
			tmp = env->next;
			free(env->key);
			free(env->value);
			free(env);
			env = tmp;
			continue;
		}
		env = env->next;
	}
	new = (t_var_env *) malloc(sizeof(t_var_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	free(key);
	free(value);
	new->next = NULL;
	env->next = new;
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

char	*var_name(char *str)
{
	char	*name;
	int		len;

	len = ft_strlen_set(str, '=');
	name = ft_substr(str, 0, len);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		ft_putstr_fd("msh: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(name);
		return (NULL);
	}
	return (name);
}

void	export_process(char **argv, t_var_env *env)
{
	char	*key;
	char	*value;
	int	i;

	i = 0;
	while (argv[++i])
	{
		key = var_name(argv[i]);
		printf("[%s]\n", key);
		if (!key)
			continue ;
		value = var_value(argv[i]);
		add_new_env(env, key, value);
	}
}

void	print_env(t_var_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
}

void	execute_export(t_msh *msh)
{
	if (!msh->cmds->argv[1])
		print_env(msh->env);
	else
		export_process(msh->cmds->argv, msh->env);
}
