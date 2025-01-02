/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obvious.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:11:49 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 08:30:16 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	check_separator(char *str, t_msh *msh)
{
	char *str_trim;

	str_trim = ft_strtrim(str, " ");
	if (str_trim[0] == '|' || str_trim[ft_strlen(str_trim) - 1] == '|')
	{
		ft_putstr_fd("Token error near |\n", 2);
		msh->ex_status = 2;
		free(str_trim);
		return (FALSE);
	}
	free(str_trim);
	return (TRUE);
}

t_bool	check_obvious_error(char *str, t_msh *msh)
{
	transform_quoted_pipe(str, msh);
	if (!unclosed_quote(str, msh) || !check_separator(str, msh)
		|| !successive_pipe(str, msh))
		return (FALSE);
	return (TRUE);
}
