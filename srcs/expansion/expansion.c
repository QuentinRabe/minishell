/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 07:20:46 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/28 08:42:09 by arabefam         ###   ########.fr       */
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

void	replace_value(char **token, t_e_env *env)
{
	char	*sub;
	char	*var_name;
	char	*last;
	char	*value;
	char	*tmp;
	int		i;
	char	delimiter;

	sub = ft_substr(*token, 0, customed_strlen(*token, '$'));
	i = customed_strlen(*token, '$') + 1;
	delimiter = check_delimiter(&(*token)[i]);
	var_name = ft_substr(*token, i, customed_strlen(&(*token)[i], delimiter));
	printf("var_name = %s\n", var_name);
	value = ft_getenv(var_name, env);
	i = i + customed_strlen(&(*token)[i], delimiter);
	last = ft_substr(*token, i, customed_strlen(&(*token)[i], '\0'));
	free(*token);
	tmp = sub;
	if (value)
		tmp = ft_strjoin(sub, value);
	free(sub);
	// free(value);
	*token = ft_strjoin(tmp, last);

	free(tmp);
	free(last);
	free(var_name);
	if (countain_dollar(*token))
		replace_value(token, env);
	return ;
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
