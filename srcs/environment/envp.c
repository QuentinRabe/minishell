/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 06:34:22 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/22 06:48:58 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_vars(t_var_env *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

static void	process(char **result, t_var_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		result[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	result[i] = NULL;
}

char	**get_env_arr(t_var_env *env)
{
	int		len;
	char	**result;

	len = count_vars(env);
	result = (char **) malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	process(result, env);
	return (result);
}
