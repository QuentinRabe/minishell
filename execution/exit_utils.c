/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:38:37 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/04 14:46:58 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	exit_process(char *arg1, char *arg2, t_ppx *data, t_msh *msh)
{
	if (arg1 && arg2 && is_only(DIGITS, arg1))
	{
		ft_putendl_fd("msh: exit : too many argument", 2);
		return (child_exit_process(data, -42), 1);
	}
	else
	{
		close(msh->historic_fd);
		if (arg1 && !is_only(DIGITS, arg1))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg1, 2);
			ft_putendl_fd(" : numeric argument required", 2);
			child_exit_process(data, 2);
			exit(2);
		}
		else if (arg1 && is_only(DIGITS, arg1))
		{
			child_exit_process(data, ft_atoi(arg1) % 256);
			exit(ft_atoi(arg1) % 256);
		}
	}
	return (0);
}
