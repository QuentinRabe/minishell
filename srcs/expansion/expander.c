/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:28:23 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/03 20:31:22 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_var	*get_last_node(t_var *var)
{
	while (var->next)
		var = var->next;
	return (var);
}

static void	build_new_token(char *token, t_var *list, t_token *curr, int i[3])
{
	char	*new;
	int		len;

	len = get_len_new_token(token, list);
	new = (char *) malloc((len + 1) * sizeof(char));
	if (!new)
		return ;
	init_array(i);
	while (token[i[0]])
	{
		if (token[i[0]] == '$' && list)
		{
			i[2] = 0;
			while (list->value && list->value[i[2]])
				new[i[1]++] = list->value[i[2]++];
			i[0] += ft_strlen(list->varname);
			increment(token, &i[0]);
			list = list->next;
		}
		else
			new[i[1]++] = token[i[0]++];
	}
	new[i[1]] = '\0';
	free(curr->value);
	curr->value = new;
}

static void	add_to_var_list(char *token, int *i, t_var **list, t_var_env *env)
{
	t_var	*new;
	t_var	*last;

	new = (t_var *) malloc(sizeof(t_var));
	if (!new)
		return ;
	new->index = *i;
	new->next = NULL;
	new->varname = get_varname(token, *i + 1);
	new->value = get_env(env, new->varname);
	if (!is_in_dq(token, *i))
		one_espace_value(new->value, new);
	*i += ft_strlen(new->varname);
	if (*list == NULL)
		*list = new;
	else
	{
		last = get_last_node(*list);
		last->next = new;
	}
}

static void	create_var_list(char *token, t_var_env *env, t_var **list)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !is_in_dq(token, i))
		{
			i++;
			while (token[i] && token[i] != '\'')
				i++;
		}
		else if (token[i] == '$')
			add_to_var_list(token, &i, list, env);
		if (token[i])
			i++;
	}
}

void	expand_variables(t_type type, t_cmd *cmds, t_var_env *env)
{
	t_token	*curr;
	t_cmd	*curr_cmd;
	t_var	*var_list;
	int		i[3];

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr = curr_cmd->token_list;
		while (curr)
		{
			if (curr->type == type)
			{
				check_filename_in_dq(curr->value, curr);
				var_list = NULL;
				create_var_list(curr->value, env, &var_list);
				build_new_token(curr->value, var_list, curr, i);
				free_var_list(var_list);
			}
			curr = curr->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
