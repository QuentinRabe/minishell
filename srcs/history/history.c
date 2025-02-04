/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:33:13 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:04 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	load_history(void)
{
	int		fd;
	char	*line;
	char	*trimed;
	t_msh	*msh;

	fd = open(".mshrc", O_RDWR | O_APPEND | O_CREAT);
	if (fd < 0)
		perror("open");
	line = get_next_line(fd);
	while (line)
	{
		trimed = ft_strtrim(line, "\n");
		add_history(trimed);
		free(line);
		free(trimed);
		line = get_next_line(fd);
	}
	msh = get_msh(1, NULL);
	msh->historic_fd = fd;
}
