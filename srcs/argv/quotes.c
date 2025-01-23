/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:13:58 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/23 15:50:35 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include <minishell.h>

static int	new_length(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	*remove_process(char *str)
{
	char	*new;
	int		len;
	int		i;
	int		j;
	char	quote;

	len = new_length(str);
	new = (char *) malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new[j++] = str[i++];
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

 void	remove_quotes(t_msh *msh)
 {
	t_cmd	*cmd;
	t_token	*tok;
	char	*tmp;

	cmd = msh->cmds;
	while (cmd)
	{
		tok = cmd->token_list;
		while (tok)
		{
			if (tok->type == WORD
				|| tok->type == INFILE
				|| tok->type == OUTFILE)
			{
				tmp = ft_strdup(tok->value);
				free(tok->value);
				tok->value = remove_process(tmp);
				free(tmp);
			}
			tok = tok->next;
		}
		cmd = cmd->next;
	}
 }
