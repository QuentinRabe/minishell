/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obvious.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:11:49 by arabefam          #+#    #+#             */
/*   Updated: 2024/12/29 12:18:37 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void check_obvious_error(char *str, t_msh *msh)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_space(str, &i);
		if (str[i] == '|')
		{
			ft_putstr_fd("Token error near |\n", 2);
			msh->ex_status = 2;
			exit(msh->ex_status);
		}
	}

}
