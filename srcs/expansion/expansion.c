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

static char	check_for_delimiter(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (*str);
		str++;
	}
	return (0);
}

static void replace_value(char **token, t_e_env *env)
{
	int i;
	char *cpy;
	char *sub;
	char *tmp;
	char *var_name;
	char delimiter;

	cpy = ft_strdup(*token);
	free(*token);
	*token = NULL;
	i = 0;
	while (cpy[i])
	{
		sub = ft_substr(cpy, i, customed_strlen(&cpy[i], '$'));
		i += customed_strlen(&cpy[i], '$');
		tmp = ft_strjoin(*token, sub);
		free(*token);
		*token = tmp;
		free(sub);
		if (cpy[i] && cpy[i] == '$' && cpy[i + 1] && (ft_isalnum(cpy[i + 1]) || cpy[i + 1] == '_'))
		{
			i++;
			delimiter = check_for_delimiter(&cpy[i]);
			var_name = ft_substr(cpy, i, customed_strlen(&cpy[i], delimiter));
			i += customed_strlen(&cpy[i], delimiter);
			tmp = ft_strjoin(*token, ft_getenv(var_name, env));
			free(*token);
			*token = tmp;
			free(var_name);
		}
		else if (cpy[i] && cpy[i] == '$')
		{
			tmp = ft_strjoin(*token, "$");
			free(*token);
			*token = tmp;
			i++;
		}
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
			if (!curr_token->in_s_quote)
				replace_value(&curr_token->value, msh->env_data.env);
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	curr_cmd = msh->cmd_lst;
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
