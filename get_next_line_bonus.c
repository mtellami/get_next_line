/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:54:40 by mtellami          #+#    #+#             */
/*   Updated: 2022/09/10 16:29:38 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	get_new_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_reminder(char **str, int i)
{
	char	*rem;
	int	len;

	len = ft_strlen(*str + i);
	rem = ft_substr(*str, i, len);
	free(*str);
	*str = NULL;
	return (rem);
}

char	*get_current_line(char **line, char **str, int i)
{
	*line = ft_substr(*str, 0, i + 1);
	*str = get_reminder(str, i + 1);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*str[8192];
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	int	size;
	int	i;

	if (!str[fd])
		str[fd] = ft_strdup("");
	size = read(fd, buffer, BUFFER_SIZE);
	while (size >= 0)
	{
		buffer[size] = 0;
		str[fd] = ft_strjoin(str[fd], buffer);
		i = get_new_line(str[fd]);
		if (i != -1)
			return (get_current_line(&line, &str[fd], i));
		if (!size && !str[fd][0])
			break ;
		if (!size)
			return (get_reminder(&str[fd], 0));
		size = read(fd, buffer, BUFFER_SIZE);
	}
	free(str[fd]);
	str[fd] = NULL;
	return (NULL);
}
