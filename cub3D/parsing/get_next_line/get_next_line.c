/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:58:03 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/28 21:33:11 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_lecture(int fd, char *buffers)
{
	char	calu[BUFFER_SIZE + 1];
	int		byte;

	byte = 1;
	while (!ft_strchr_my(buffers, '\n') && byte)
	{
		byte = read(fd, calu, BUFFER_SIZE);
		if (byte == -1)
			return (0);
		calu[byte] = '\0';
		buffers = ft_strjoineb(buffers, calu);
	}
	return (buffers);
}

char	*lire_ligne(char *buffers)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!buffers[i])
		return (0);
	while (buffers[i] != '\n' && buffers[i] != '\0')
		i++;
	if (buffers[i] == '\n')
		i++;
	tmp = (char *)malloc(sizeof (char) * i + 1);
	if (!tmp)
		return (0);
	i = 0;
	while (buffers[i] != '\n' && buffers[i] != '\0')
	{
		tmp[i] = buffers[i];
		i++;
	}
	if (buffers[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

char	*rest(char *buffers)
{
	int		i;
	char	*rest;
	int		len;
	int		j;

	i = 0;
	j = 0;
	while (buffers[i] != '\n' && buffers[i])
		i++;
	if (!buffers[i])
	{
		free (buffers);
		return (0);
	}
	len = ft_strleen(buffers) - i;
	rest = (char *)malloc(sizeof (char) * len + 1);
	if (!rest)
		return (0);
	i++;
	while (buffers[i])
		rest[j++] = buffers[i++];
	rest[j] = '\0';
	free (buffers);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffers;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	buffers = ft_lecture(fd, buffers);
	if (!buffers)
		return (0);
	line = lire_ligne(buffers);
	if (!line)
		return (0);
	buffers = rest(buffers);
	return (line);
}
