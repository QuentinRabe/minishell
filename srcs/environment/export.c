/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:32:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/12 13:32:26 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_e_env	*find_last_node(t_e_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

static char	*extract_value(char *env_var, int *i)
{
	char	*result;
	int		length;

	length = customed_strlen(&env_var[*i], '\0');
	result = ft_substr(env_var, *i, length);
	return (result);
}

static char *extract_key(char *env_var, int *i)
{
	char	*result;
	int		length;

	length = customed_strlen(&env_var[*i], '=');
	result = ft_substr(env_var, *i, length);
	*i += length + 1;
	return (result);
}

static void	add_env_var(t_e_env **env, char *env_var)
{
	t_e_env	*new;
	t_e_env	*last;
	int		i;

	new = (t_e_env *) malloc(sizeof(t_e_env));
	if (!new)
		return ;
	i = 0;
	new->next = NULL;
	new->key = extract_key(env_var, &i);
	new->value = extract_value(env_var, &i);
	if (!*env)
	{
		*env = new;
		new->prev = NULL;
	}
	else
	{
		last = find_last_node(*env);
		last->next = new;
		new->prev = last;
	}
}

void	create_exp_lst(t_e_env **ex_env, char **env_vars)
{
	int	i;

	*ex_env = NULL;
	i = -1;
	while (env_vars[++i])
		add_env_var(ex_env, env_vars[i]);
	sort_export_env(ex_env);
	// while (ex_env)
	// {
	// 	printf("%s=%s\n", ex_env->key, ex_env->value);
	// 	ex_env = ex_env->next;
	// }
}