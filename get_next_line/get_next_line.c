/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:17:26 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/12 18:40:42 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_stash(&stash, fd);
	if (!stash)
		return (NULL);
	extract_line(stash, &line);
	if (*line == '\0')
	{
		*stash = NULL;
		free(line);
		return (NULL);
	}
	clean_stash(&stash);
	return (line);
}

void	read_and_stash(char **stash, int fd)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	while (!found_newline(stash))
	{
		if (!buffer)
		{
			free (buffer);
			return ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		ft_strjoin(buffer, stash);
	}
	free(buffer);
}

void	extract_line(char *stash, char	**line)
{
	size_t	len;

	len = ft_strlen(stash);
	*line = malloc(sizeof(char) * len + 1);
	if (!line)
	{
		free (line);
		return ;
	}
	ft_strjoin(stash, *line);
	return ;
}

void	clean_stash(char **stash)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(stash);
	temp = malloc (sizeof(char) * len);
	if (!temp)
	{
		free (temp);
		return ;
	}
	while (stash != '\n')
		*stash++;
	*stash++;
	while (*stash != '\0')
		*temp++ = *stash++;
	*temp = '\0';
	*stash = NULL;
	stash = *temp;
}

