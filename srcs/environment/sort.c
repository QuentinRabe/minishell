/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:49:25 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/05 18:22:03 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap(t_var_env *a, t_var_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_list_env(t_var_env **env)
{
	t_var_env	*curr;
	t_var_env	*next;
	t_var_env	*min;

	curr = *env;
	while (curr)
	{
		min = curr;
		next = curr->next;
		while (next)
		{
			if (ft_strcmp(min->key, next->key) > 0)
				min = next;
			next = next->next;
		}
		if (min != curr)
			swap(min, curr);
		curr = curr->next;
	}
}
