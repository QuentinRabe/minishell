/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:52:54 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 08:09:20 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_env(t_msh *msh, char **env)
{
	create_env_lst(&msh->env_data.env, env);
	create_exp_lst(&msh->env_data.ex_env, env);
}
