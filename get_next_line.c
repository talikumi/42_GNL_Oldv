/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:22:55 by ntozzi            #+#    #+#             */
/*   Updated: 2021/02/08 10:26:05 by ntozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*scan_line(char *str, int fd, int *toread)
{
	char			*tmp;
	char			buf[BUFFER_SIZE + 1];

	*toread = read(fd, buf, BUFFER_SIZE);
	while ((*toread) > 0)
	{
		buf[*toread] = '\0';
		if (str == NULL)
			str = ft_strdup(buf);
		else
		{
			tmp = str;
			str = ft_strjoin(str, buf);
			free(tmp);
		}
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (str);
}

int	get_line(char *str, char **line)
{
	int				i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
		{
			*line = ft_substr(str, 0, i);
			return (1);
		}
		else
		{
			*line = ft_strdup(str);
			return (0);
		}
	}
	else
	{
		*line = ft_strdup("");
		return (0);
	}
}

char	*buffer_left(char *str)
{
	char			*tmp;
	int				i;
	int				str_len;

	i = 0;
	str_len = ft_strlen(str);
	if (str != NULL)
	{
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
		{
			tmp = str;
			str = ft_substr(str, i + 1, str_len - i - 1);
			free(tmp);
		}
	}
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char		*str[2000];
	int				buffer_excess;
	int				nbr;

	if (read(fd, str[fd], 0) || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	str[fd] = scan_line(str[fd], fd, &nbr);
	if (nbr < 0)
		return (-1);
	buffer_excess = get_line(str[fd], line);
	if (buffer_excess)
		str[fd] = buffer_left(str[fd]);
	else
	{
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	return (1);
}
