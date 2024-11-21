/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 07:20:46 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/18 07:20:46 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token(t_cmd *cmd_lst)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;

	curr_cmd = cmd_lst;
	while (curr_cmd)
	{
		curr_token = curr_cmd->token_lst;
		while (curr_token)
		{
			printf("[value %s]\n", curr_token->value);
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
}

static t_bool	countain_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

static char	check_for_delimiter(char *str)
{
	while (*str)
	{
		if ((!ft_isalnum(*str) && *str != '_') || *str == '?')
			return (*str);
		str++;
	}
	return (0);
}

static void	join_values(char *cpy, int *i, char **token, t_e_env *env)
{
	char	delimiter;
	char	*var_name;
	char	*tmp;
	char	*value;

	if (cpy[*i] && cpy[*i] == '$' && cpy[*i + 1]
		&& (ft_isalnum(cpy[*i + 1]) || cpy[*i + 1] == '_'))
	{
		*i += 1;
		delimiter = check_for_delimiter(&cpy[*i]);
		var_name = ft_substr(cpy, *i, customed_strlen(&cpy[*i], delimiter));
		if (!var_name)
			return ;
		*i += customed_strlen(&cpy[*i], delimiter);
		value = ft_getenv(var_name, env);
		if (value)
			tmp = ft_strjoin(*token, value);
		else
			tmp = ft_strjoin(*token, "");
		free(*token);
		*token = ft_strdup(tmp);
		free(tmp);
		free(var_name);
	}
	else if (cpy[*i] && cpy[*i] == '$')
	{
		tmp = ft_strjoin(*token, "$");
		free(*token);
		*token = ft_strdup(tmp);
		free(tmp);
		*i += 1;
	}
}

static void	replace_value(char **token, t_e_env *env)
{
	int		i;
	char	*cpy;
	char	*sub;
	char	*tmp;

	cpy = ft_strdup(*token);
	free(*token);
	*token = NULL;
	i = 0;
	while (cpy[i])
	{
		sub = ft_substr(cpy, i, customed_strlen(&cpy[i], '$'));
		i += customed_strlen(&cpy[i], '$');
		if (*token)
		{
			tmp = ft_strjoin(*token, sub);
			free(*token);
		}
		else
			tmp = sub;
		*token = ft_strdup(tmp);
		free(tmp);
		join_values(cpy, &i, token, env);
	}
	free(cpy);
}

void	expand_vars(t_msh *msh)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;

	curr_cmd = msh->cmd_lst;
	while (curr_cmd)
	{
		curr_token = curr_cmd->token_lst;
		while (curr_token)
		{
			if (!curr_token->in_s_quote && countain_dollar(curr_token->value))
				replace_value(&curr_token->value, msh->env_data.env);
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	print_token(msh->cmd_lst);
}
