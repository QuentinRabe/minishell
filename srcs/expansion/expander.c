/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:28:23 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 10:17:33 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_len_new_token(char *token, t_var *list)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && list)
		{
			len += ft_strlen(list->value);
			i += ft_strlen(list->varname) + 1;
			list = list->next;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	build_new_token(char *token, t_var *list, t_token *curr_token)
{
	char	*new;
	int		len;
	int		i;
	int		j;
	int		k;

	len = get_len_new_token(token, list);
	new = (char *) malloc((len + 1) * sizeof(char));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$' && list)
		{
			k = 0;
			while (list->value[k])
				new[j++] = list->value[k++];
			i += ft_strlen(list->varname) + 1;
			list = list->next;
		}
		else
			new[j++] = token[i++];
	}
	new[j] = '\0';
	curr_token->value = new;
}

bool	count_if_quote_case(char *token, int *count)
{
	int		i;
	char	quote;

	i = -1;
	if (token[0] == '\'' || token[0] == '"')
	{
		while (token[++i])
		{
			if (token[i] == '"' || token[i] == '\'')
			{
				quote = token[i++];
				*count += 1;
				if ((quote == '"' && is_in_dq(token, i))
					|| (quote == '\'' && is_in_sq(token, i)))
				{
					while (token[i] && token[i] != quote)
					{
						*count += 1;
						i++;
					}
					if (token[i])
						*count += 1;
					return (true);
				}
			}
		}
	}
	return (false);
}

int	get_varlen(char *token)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	if (!count_if_quote_case(token, &count))
	{
		while (token[++i])
		{
			if (ft_isalnum(token[i]))
				count++;
			else if (!ft_isalnum(token[i]) && (token[i] == '?' || token[i] == '$') && i == 0)
				return (1);
			else if ((!ft_isalnum(token[i]) && token[i] == '_'))
				count++;
			else if (!ft_isalnum(token[i]))
				return (count);
		}
	}
	return (count);
}

static t_var	*get_last_node(t_var *var)
{
	while (var->next)
		var = var->next;
	return (var);
}

char	*get_varname(char *token, int i)
{
	char	*varname;
	int		varlen;
	int		j;

	varlen = get_varlen(token + i);
	if (varlen == 0)
		return (ft_strdup("$"));
	varname = (char *) malloc((varlen + 1) * sizeof(char));
	if (!varname)
		return (NULL);
	j = 0;
	while (varlen > 0)
	{
		varname[j++] = token[i++];
		varlen--;
	}
	varname[j] = '\0';
	return (varname);
}

void	add_to_var_list(char *token, int *i, t_var **list, t_var_env *env)
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
	*i += ft_strlen(new->varname);
	if (*list == NULL)
		*list = new;
	else
	{
		last = get_last_node(*list);
		last->next = new;
	}
}

bool	is_in_sq(char *token, int i)
{
	int		tmp;
	int		count;

	tmp = i;
	count = 0;
	while (i >= 0)
	{
		if (token[i] && token[i] == '\'')
		{
			count++;
			break;
		}
		i--;
	}
	i = tmp;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			count++;
			break;
		}
		i++;
	}
	if (count == 2)
		return (true);
	else
		return (false);
}

bool	is_in_dq(char *token, int i)
{
	int		tmp;
	int		count;

	tmp = i;
	count = 0;
	while (i >= 0)
	{
		if (token[i] && token[i] == '"')
		{
			count++;
			break;
		}
		i--;
	}
	i = tmp;
	while (token[i])
	{
		if (token[i] == '"')
		{
			count++;
			break;
		}
		i++;
	}
	if (count == 2)
		return (true);
	else
		return (false);
}

void	create_var_list(char *token, t_var_env *env, t_var **list)
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

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr = curr_cmd->token_lis;
		while (curr)
		{
			var_list = NULL;
			if (curr->type == type)
			{
				create_var_list(curr->value, env, &var_list);
				build_new_token(curr->value, var_list, curr);
				free_var_list(var_list);
			}
			curr = curr->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
