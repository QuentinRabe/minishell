/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/06 11:13:28 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_env	vars;
	int		i;

	(void) ac,
	(void) av;
	(void) env;
	i = -1;
	vars.path = extract_path_from_env(env);
	while (vars.path[++i])
		printf("%s\n", vars.path[i]);
	i = -1;
	while (vars.path[++i])
		free(vars.path[i]);
	free(vars.path);
	return (0);
}
