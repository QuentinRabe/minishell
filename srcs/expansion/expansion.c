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
			free(sub);
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
}
