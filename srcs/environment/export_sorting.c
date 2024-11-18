/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:34:31 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/12 13:34:40 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void insert_sorted(t_e_env **sorted, t_e_env *new_node)
{
	t_e_env *current;

	if (*sorted == NULL || ft_strcmp((*sorted)->key, new_node->key) >= 0)
	{
		new_node->next = *sorted;
		new_node->prev = NULL;
		if (*sorted != NULL)
			(*sorted)->prev = new_node;
		*sorted = new_node;
	}
	else
	{
		current = *sorted;
		while (current->next != NULL && ft_strcmp(current->next->key, new_node->key) < 0)
			current = current->next;
		new_node->next = current->next;
		if (current->next != NULL)
			current->next->prev = new_node;
		current->next = new_node;
		new_node->prev = current;
	}
}

void sort_export_env(t_e_env **exp)
{
	t_e_env *sorted;
	t_e_env *current;
	t_e_env *next;

	sorted = NULL;
	current = *exp;
	while (current != NULL)
	{
		next = current->next;
		current->next = NULL;
		current->prev = NULL;
		insert_sorted(&sorted, current);
		current = next;
	}
	*exp = sorted;
}