/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:55:33 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/13 19:05:28 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stash(&stash, fd);
	if (!stash)
		return (NULL);
 	extract_line(stash, &line);
	clean_stash(&stash, line);
	return (line);
}

void	read_and_stash(char **stash, int fd)
{
	char	*buffer;
	int		bytes_read;
	int		len;

	bytes_read = 1;
	len = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(*stash, '\n') && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		len += bytes_read;
		*stash = ft_strjoin(len, *stash, buffer);
	}
}

void	extract_line(char *stash, char **line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	*line = malloc(sizeof(char) * (i + 1));
	while (len < i)
	{
		(*line)[len] = stash[len];
		len++;
	}
	(*line)[len] = '\0';
}

void clean_stash(char **stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i] == '\0')
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(*stash) - i + 1));
	i++;
	while ((*stash)[i] != '\0')
		new_stash[j++] = (*stash)[i++];
	new_stash[j] = '\0';
	free(*stash);
	*stash = new_stash;
}

int	ft_strchr(char *str, char c)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strjoin(int len, char *s1, char *s2)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1 != '\0')
			new_str[i++] = *s1++;
	while (*s2 != '\0')
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str != '\0')
		len++;
	return (len);
}

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int		main()
{
	int		fd;
	char	*line;

	fd = open("hp1.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
}
