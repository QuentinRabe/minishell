/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rravelom <rravelom@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:03:31 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/18 10:03:32 by rravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h" 

int	ft_error(char *msg, char *cause, int stat)
{
	int	size;
	int	len;

	len = ft_strlen(cause);
	size = ft_strlen(msg);
	write (2, "Error: ", 7);
	write (2, msg, size);
	if (cause != NULL)
		write (2, cause, len);
	write (2, "\n", 2);
	exit (stat);
}
