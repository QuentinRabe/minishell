/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 07:38:27 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/21 14:13:56 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_var	*get_last_node(t_var *var)
{
	while (var->next)
		var = var->next;
	return (var);
}

static void	build_new_token_hd(char **input, t_var *list, int i[3])
{
	char	*new;
	int		len;

	len = get_len_new_input_hd(*input, list);
	new = (char *) malloc((len + 1) * sizeof(char));
	if (!new)
		return ;
	i[0] = 0;
	i[1] = 0;
	while ((*input)[i[0]])
	{
		if ((*input)[i[0]] == '$' && list && list->index == i[0])
		{
			i[2] = 0;
			while (list->value[i[2]])
				new[i[1]++] = list->value[i[2]++];
			i[0] += ft_strlen(list->varname) + 1;
			list = list->next;
		}
		else
			new[i[1]++] = (*input)[i[0]++];
	}
	new[i[1]] = '\0';
	(*input) = ft_strdup(new);
	free(new);
}

static void	add_to_var_list_hd(char *token, int *i, \
t_var **list, t_var_env *env)
{
	t_var	*new;
	t_var	*last;

	new = (t_var *) malloc(sizeof(t_var));
	if (!new)
		return ;
	new->index = *i;
	new->next = NULL;
	new->varname = get_varname_hd(token, *i + 1);
	printf("varname->%s\n", new->varname);
	new->value = get_env(env, new->varname);
	printf("value->%s\n", new->value);
	*i += ft_strlen(new->varname);
	if (*list == NULL)
		*list = new;
	else
	{
		last = get_last_node(*list);
		last->next = new;
	}
}

static void	create_var_list_hd(char *token, t_var_env *env, t_var **list)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1]
			&& (ft_isalnum(token[i + 1])
				|| token[i + 1] == '_'))
			add_to_var_list_hd(token, &i, list, env);
		if (token[i])
			i++;
	}
}

void	expand_input(char **input, t_var_env *env)
{
	t_var	*list;
	int		i[3];

	list = NULL;
	create_var_list_hd(*input, env, &list);
	build_new_token_hd(input, list, i);
	free_var_list(list);
}
