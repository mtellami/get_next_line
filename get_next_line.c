/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:29:44 by mtellami          #+#    #+#             */
/*   Updated: 2022/09/07 18:37:37 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*str;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	int	size;
	int	i;

	if (!str)
		str = ft_strdup("");
	size = read(fd, buffer, BUFFER_SIZE);
	while (size >= 0)
	{
		buffer[size] = 0;
		str = ft_strjoin(str, buffer);
		i = get_new_line(str);
		if (i != -1)
			return (get_current_line(&line, &str, i));
		if (!size && !str[0])
			break ;
		if (!size)
			return (get_reminder(&str, 0));
		size = read(fd, buffer, BUFFER_SIZE);
	}
	free(str);
	str = NULL;
	return (NULL);
}
