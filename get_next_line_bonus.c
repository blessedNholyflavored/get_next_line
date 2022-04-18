/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:55:08 by lkhamlac          #+#    #+#             */
/*   Updated: 2021/12/09 18:50:33 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *str)
{
	char	*buffer;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (!(*str))
		return (free(str), NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		++i;
	buffer = malloc(sizeof(char) * (i + 1));
	if (!buffer)
		return (0);
	i = -1;
	while (str[++i] && str[i] != '\n')
		buffer[i] = str[i];
	buffer[i] = str[i];
	if (str[i] == '\n')
		buffer[++i] = '\0';
	return (buffer);
}

char	*ft_rest(char *line)
{
	int		i;
	int		j;
	char	*reste;

	i = 0;
	j = 0;
	if (!line || !line[0])
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (free(line), NULL);
	reste = (char *)malloc(ft_strlen(&line[i]));
	if (!reste)
		return (NULL);
	i++;
	while (line[i])
		reste[j++] = line[i++];
	reste[j] = '\0';
	free(line);
	return (reste);
}

char	*get_next_line_bonus(int fd)
{
	char		*line;
	char		*buff;
	int			i;
	static char	*reste[1024];

	line = NULL;
	i = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (has_bn(reste[fd]) == 0 && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (free(buff), NULL);
		buff[i] = '\0';
		reste[fd] = ft_strjoin(reste[fd], buff);
	}
	free(buff);
	line = ft_line(reste[fd]);
	reste[fd] = ft_rest(reste[fd]);
	return (line);
}
