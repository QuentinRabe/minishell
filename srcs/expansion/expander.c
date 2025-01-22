/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:28:23 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/22 13:40:13 by arabefam         ###   ########.fr       */
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
	i[0] = 0;
	i[1] = 0;
	while (token[i[0]])
	{
		if (token[i[0]] == '$' && list)
		{
			i[2] = 0;
			while (list->value && list->value[i[2]])
				new[i[1]++] = list->value[i[2]++];
			i[0] += ft_strlen(list->varname);
			list = list->next;
		}
		else
			new[i[1]++] = token[i[0]++];
	}
	new[i[1]] = '\0';
	if (ft_strcmp(new, curr->value))
		curr->expanded = true;
	free(curr->value);
	curr->value = new;
}

 size_t	get_splitted_lenght(char **splitted, int *spaces)
{
	int		i;
	int		j;
	size_t	len;

	len = 0;
	i = -1;
	while (splitted[++i])
	{
		j = -1;
		while (splitted[i][++j])
			len++;
		(*spaces)++;
	}
	(*spaces)--;
	return (len);
}

 void	create_new_value(char *new, char **splitted)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	while (splitted[++i])
	{
		j = -1;
		while (splitted[i][++j])
			new[k++] = splitted[i][j];
		new[k++] = ' ';
	}
	new[--k] = '\0';
	free_argv(splitted);
}

 void	one_espace_value(char *value, t_var *new)
{
	char	*new_value;
	char	**splitted;
	int		spaces;
	size_t	len;

	spaces = 0;
	splitted = ft_split_set(value, SPACES);
	len = get_splitted_lenght(splitted, &spaces);
	new_value = (char *) malloc((len + spaces + 1) * sizeof(char));
	if (!new_value)
		return ;
	create_new_value(new_value, splitted);
	free(value);
	new->value = ft_strdup(new_value);
	free(new_value);
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
	printf("varname->%s\n", new->varname);
	if (!ft_strcmp(new->varname, "$")
		&& token[*i + 1] == '"')
		new->value = ft_strdup("$\"");
	else
		new->value = get_env(env, new->varname);
	if (is_in_dq(token, *i))
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
	int		it;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr = curr_cmd->token_list;
		while (curr)
		{
			it = -1;
			while (curr->type == type && ++it < 2)
			{
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
