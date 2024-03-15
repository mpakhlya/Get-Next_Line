/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpakhlya <mpakhlya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:49:48 by mpakhlya          #+#    #+#             */
/*   Updated: 2024/02/05 18:49:48 by mpakhlya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buff)
{
	char	*temp;

	temp = ft_strjoin(buffer, buff);
	free(buffer);
	return (temp);
}

char	*ft_prochain(char *buffer)
{
	int		i;
	int		j;
	char	*la_ligne;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	la_ligne = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		la_ligne[j++] = buffer[i++];
	free(buffer);
	return (la_ligne);
}

char	*ft_la_ligne(char *buffer)
{
	char	*la_ligne;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	la_ligne = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		la_ligne[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		la_ligne[i++] = '\n';
	return (la_ligne);
}

char	*lire_ficher(int fd, char *res)
{
	char	*buffer;
	int		byte_lire;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_lire = 1;
	while (byte_lire > 0)
	{
		byte_lire = read(fd, buffer, BUFFER_SIZE);
		if (byte_lire == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[byte_lire] = 0;
		res = ft_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*la_ligne;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = lire_ficher(fd, buffer);
	if (!buffer)
		return (NULL);
	la_ligne = ft_la_ligne(buffer);
	buffer = ft_prochain(buffer);
	return (la_ligne);
}
