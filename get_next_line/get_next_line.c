/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:19:53 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/06 18:00:29 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	//error handling
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = NULL;
	line = NULL;
	//read and add to stash
	read_and_stash(&stash, fd);
	//extract line
	extract_line(&stash, &line);
	//clean stash
	//return line or handle end of file
	return (line);
}

void read_and_stash(t_list **stash, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!found_newline(stash))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && bytes_read == 0) || bytes_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		if (add_to_stash(stash, buffer, bytes_read) == 0)
		{
			free(buffer);
			return ;
		}
		free (buffer);
	}
}
