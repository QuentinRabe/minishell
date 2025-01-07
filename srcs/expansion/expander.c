/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:28:23 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/07 13:26:05 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_varlen(char *token)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
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

	(void) list;
	(void) env;
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

void	create_var_list(char *token, t_var_env *env, t_var **list)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] != '\'')
				i++;
		}
		else if (token[i] == '$')
			add_to_var_list(token, &i, list, env);
	}
}

void	expand_variables(t_type type, t_cmd *cmds, t_var_env *env)
{
	t_token	*curr;
	t_cmd	*curr_cmd;
	t_var	*curr_var;

	(void) type;
	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr = curr_cmd->token_lis;
		while (curr)
		{
			curr->var_list = NULL;
			if (curr->type == type)
				create_var_list(curr->value, env, &curr->var_list);
			curr = curr->next;
		}
		curr_cmd = curr_cmd->next;
	}
	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr = curr_cmd->token_lis;
		while (curr)
		{
			curr_var = curr->var_list;
			while (curr_var)
			{
				printf("[%s=%s]\n", curr_var->varname, curr_var->value);
				curr_var = curr_var->next;
			}
			curr = curr->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
