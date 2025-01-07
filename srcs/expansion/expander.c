/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 07:28:23 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/07 11:07:13 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_varlen(char *token)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	printf("%s\n", token);
	while (token[++i])
	{
		if (ft_isalnum(token[i]))
		{
			printf("[%c]\n", token[i]);
			count++;
		}
		else if (!ft_isalnum(token[i]) && (token[i] == '?' || token[i] == '$') && i == 0)
			return (1);
		else if ((!ft_isalnum(token[i]) && token[i] == '_'))
		{
			printf("_[%c]\n", token[i]);
			count++;
		}
		else if (!ft_isalnum(token[i]))
			return (count);
	}
	return (count);
}

char	*get_varname(char *token, int i)
{
	char	*varname;
	int		varlen;
	int		j;

	varlen = get_varlen(token + i);
	printf("len[%d]\n", varlen);
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

void	add_to_var_list(char *token, int i, t_var **list, t_var_env *env)
{
	t_var	*new;

	(void) list;
	(void) env;
	new = (t_var *) malloc(sizeof(t_var));
	if (!new)
		return ;
	new->index = i;
	new->next = NULL;
	new->varname = get_varname(token, i + 1);
	printf("varname=[%s]\n", new->varname);
}

void	create_var_list(char *token, t_var_env *env, t_var **list)
{
	int	i;

	i = -1;
	*list = NULL;
	while (token[++i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] != '\'')
				i++;
		}
		else if (token[i] == '$')
			add_to_var_list(token, i, list, env);
	}
}

void	expand_variables(t_type type, t_cmd *cmds, t_var_env *env)
{
	t_token	*curr;

	(void) type;
	while (cmds)
	{
		curr = cmds->token_lis;
		while (curr)
		{
			printf("hello\n");
			create_var_list(curr->value, env, &curr->var_list);
			curr = curr->next;
		}
		cmds = cmds->next;
	}
}
