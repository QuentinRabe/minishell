/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:35:57 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/07 15:59:01 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	custom_strlen(char *str, char charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] != charset)
	{
		i++;
		counter++;
	}
	return (counter);
}

static void	insert_tokens(t_token *tokens, int n_token, char *str)
{
	int		i;
	int		j;
	int		length;
	char	quote;

	(void) n_token;
	i = 0;
	j = -1;
	while (str[++j])
	{
		while (str[j] && is_space(str[j]))
			j++;
		if ((str[j] == '\'' || str[j] == '"') && str[j])
		{
			quote = str[j];
			j++;
			length = custom_strlen(&str[j], quote);
			printf("Length = %d\n", length);
			tokens[i].value = ft_substr(str, j, length );
			j += length;
			i++;
		}
		else if (str[j] && !is_space(str[j]))
		{
			length = custom_strlen(&str[j], ' ');
			tokens[i].value = ft_substr(str, j, length);
			j += length;
			i++;
		}
	}
}

static int count_tokens(char *str)
{
	int		i;
	int		counter;
	char	quote;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if ((str[i] == '\'' || str[i] == '"') && str[i])
		{
			counter++;
			quote = str[i];
			i++;
			while (str[i] != quote && str[i])
				i++;
			if (str[i] == quote)
				i++;
		}
		else
		{
			counter++;
			while (str[i] && !is_space(str[i]))
				i++;
		}
	}
	return (counter);
}

static void	tokenize_cmd(char **array, t_cmd *cmds)
{
	int	i;
	int	n_tokens;

	i = -1;
	while (array[++i])
	{
		n_tokens = count_tokens(array[i]);
		cmds[i].tokens = (t_token *) malloc(n_tokens * sizeof(t_token));
		insert_tokens(cmds[i].tokens, n_tokens, array[i]);
	}
}

static int	count_cmds(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		;
	return (i);
}

void	init_tokenization(char *str)
{
	char	**splitted;
	t_cmd	*cmds;
	int		n_cmds;

	splitted = ft_split(str, '|');
	n_cmds = count_cmds(splitted);
	cmds = (t_cmd *) malloc(n_cmds * sizeof(t_cmd));
	tokenize_cmd(splitted, cmds);
	int i = -1;
	while (++i < n_cmds)
	{
		printf("%d\n", count_tokens(splitted[i]));
		int j = 0;
		while (j < count_tokens(splitted[i]))
		{
			printf("Cmd %d Token %d -> %s\n", i + 1, j + 1, cmds[i].tokens[j].value);
			j++;
		}
	}
}
