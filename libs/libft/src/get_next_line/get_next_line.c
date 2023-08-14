/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:48:13 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/26 18:48:30 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"
#include "ft_libft.h"
#include "ft_stdlib.h"
#include "ft_string.h"

size_t		ft_strclen(const char *s, char c);

static char	*ft_free_and_add(char *s_buffer, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(s_buffer, buffer);
	free(s_buffer);
	return (tmp);
}

static char	*ft_read_file(int fd, char *s_buffer)
{
	char	*buffer;
	int		r;

	if (!s_buffer)
		s_buffer = ft_calloc(sizeof(char), 1);
	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	r = 1;
	while (r > 0)
	{
		r = (int)read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[r] = '\0';
		s_buffer = ft_free_and_add(s_buffer, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (s_buffer);
}

static char	*ft_add_clean(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer[0])
		return (NULL);
	line = ft_calloc(sizeof(char), ft_strclen(buffer, '\n') + 2);
	if (!line)
		return (NULL);
	line[ft_strclen(buffer, '\n') + 1] = '\0';
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	return (line);
}

static char	*ft_re_buffer(char *buffer)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = ft_strclen(buffer, '\n');
	if (!buffer[i])
		return (free(buffer), NULL);
	tmp = ft_calloc(sizeof(char), ft_strlen(buffer) - i + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	i++;
	while (buffer[i])
	{
		tmp[j] = buffer[i];
		i++;
		j++;
	}
	return (free(buffer), tmp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_add_clean(buffer);
	buffer = ft_re_buffer(buffer);
	return (line);
}
