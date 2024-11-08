/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:35:57 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 11:11:50 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

static void	tokenize_cmd(char **splt_cmd, t_cmd *cmd_arr)
{
	int	i;
	int	n_tokens;

	i = -1;
	while (splt_cmd[++i])
	{
		n_tokens = count_tokens(splt_cmd[i]);
		cmd_arr[i].tokens = (t_token *) malloc(n_tokens * sizeof(t_token));
		create_tokens(cmd_arr[i].tokens, splt_cmd[i]);
	}
}

void	init_tokenization(char *str, t_cmd *cmd_arr)
{
	char	**splitted;
	int		n_cmds;
	int		i;
	int		j;

	splitted = ft_split(str, '|');
	n_cmds = count_cmds(splitted);
	cmd_arr = (t_cmd *) malloc(n_cmds * sizeof(t_cmd));
	//free if failed
	tokenize_cmd(splitted, cmd_arr);
	i = -1;
	while (++i < n_cmds)
	{
		j = -1;
		while (cmd_arr[i].tokens[++j].value)
			print_tokens(&cmd_arr[i].tokens[j], i, j);
	}
	    i = 0;
    while (splitted[i])
    {
        free(splitted[i]);
        i++;
    }
    free(splitted);
}
