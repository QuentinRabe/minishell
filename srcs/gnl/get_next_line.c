/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:46:46 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 14:00:07 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = fill_store(fd, store);
	if (!store)
		return (free(store), NULL);
	line = extract_line(store);
	store = clean_store(store);
	return (line);
}

char	*fill_store(int fd, char *store)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	while (!(contain_newline(store)) && bytes_read != 0)
	{
		buffer = (char *) malloc((BUFFER_SIZE + 1) * (sizeof(char)));
		if (!buffer)
			return (free(buffer), NULL);
		bytes_read = (int) read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(store), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		store = ft_strjoin_gnl(store, buffer);
		free(buffer);
	}
	return (store);
}

char	*extract_line(char *store)
{
	char	*extracted;
	int		len;
	int		i;

	i = 0;
	if (!store[i])
		return (NULL);
	len = get_len(store);
	extracted = (char *) malloc((len + 1) * sizeof(char));
	if (!extracted)
		return (free(extracted), NULL);
	while (store[i] != '\0' && store[i] != '\n')
	{
		extracted[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
	{
		extracted[i] = store[i];
		i++;
	}
	extracted[i] = '\0';
	return (extracted);
}

char	*clean_store(char *store)
{
	char	*new_store;
	int		i;
	int		j;

	i = 0;
	while ((store)[i] != '\0' && (store)[i] != '\n')
		i++;
	if (!store[i])
		return (free(store), NULL);
	new_store = malloc((ft_strlen_gnl((store + i), '\0') + 1) * sizeof(char));
	if (!new_store)
		return (free(new_store), NULL);
	j = 0;
	i++;
	while ((store)[i] != '\0')
		new_store[j++] = (store)[i++];
	new_store[j] = '\0';
	return (free(store), new_store);
}
