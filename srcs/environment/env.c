/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:29:46 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/05 14:56:07 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_var_env	*get_last_node(t_var_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

static char	*get_value(char *arg)
{
	char	*value;
	int		i;
	int		len;
	int		j;

	i = (ft_strlen_set(arg, '='));
	len = (ft_strlen_set(&arg[++i], '\0'));
	value = (char *) malloc((len + 1) * sizeof(char));
	if (!value)
		return (NULL);
	j = -1;
	while (++j < len)
		value[j] = arg[i++];
	value[j] = '\0';
	return (value);
}

static char	*get_key(char *arg)
{
	char	*key;
	int		i;
	int		len;

	len = (ft_strlen_set(arg, '='));
	key = (char *) malloc((len + 1) * sizeof(char));
	if (!key)
		return (NULL);
	i = -1;
	while (++i < len)
		key[i] = arg[i];
	key[i] = '\0';
	return (key);
}

static void	add_to_list(t_var_env **env, char *arg)
{
	t_var_env	*new;
	t_var_env	*last;

	new = (t_var_env *) malloc(sizeof(t_var_env));
	if (!new)
		return ;
	new->key = get_key(arg);
	new->value = get_value(arg);
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
	{
		last = get_last_node(*env);
		last->next = new;
	}
}

void	get_var_env(t_var_env **env, char **args)
{
	int			i;

	i = -1;
	*env = NULL;
	while (args[++i])
		add_to_list(env, args[i]);
}
