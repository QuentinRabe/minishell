/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:41:24 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/12 12:41:24 by arabefam         ###   ########.fr       */
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
		*env = new;
	else
	{
		last = find_last_node(*env);
		last->next = new;
	}

}

void	create_env_lst(t_e_env *env, char **env_vars)
{
	int	i;

	env = NULL;
	i = -1;
	while (env_vars[++i])
		add_env_var(&env, env_vars[i]);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}