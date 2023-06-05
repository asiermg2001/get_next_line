/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 08:57:53 by amarcos-          #+#    #+#             */
/*   Updated: 2023/05/30 10:29:59 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinfree(char *s1, char *s2)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	free(s1);
	return (aux);
}

char	*read_file(int fd, char *buffer)
{
	char	*buf;
	int		i;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	i = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
			return (free(buf), NULL);
		else
		{
			buf[i] = 0;
			buffer = ft_joinfree(buffer, buf);
			if (ft_strchr(buf, '\n'))
				break ;
		}
	}
	free(buf);
	return (buffer);
}

char	*read_nextline(char *buffer)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	str = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!str)
		return (NULL);
	i++;
	while (buffer[i])
		str[j++] = buffer[i++];
	free(buffer);
	return (str);
}

char	*read_line(char *buffer)
{
	char	*str;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		str[i++] = '\n';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*readline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	readline = read_line(buffer);
	buffer = read_nextline(buffer);
	return (readline);
}
