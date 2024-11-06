/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/06 10:13:55 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	// char	*path;

	(void) ac,
	(void) av;
	(void) env;
	path = get_prompt_cwd();
	readline(path);
	free(path);
	return (0);
}
