/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:52:21 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/11 22:58:06 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	if (!stash)
		stash = NULL;
	line = NULL;
	read_and_stash(&stash, fd);
	if (!stash)
		return (NULL);
	extract_line(stash, &line);
	if (line[0] == '\0')
	{
		clean_stash(&stash);
		free(line);
		return (NULL);
	}
	clean_stash(&stash);
	return (line);
}

void	read_and_stash(t_list **stash, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	while (!found_newline(*stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*stash && ((*stash)->content[0] == '\0' && bytes_read == 0))
			return ;
		buffer[bytes_read] = '\0';
		add_to_stash(stash, buffer, bytes_read);
	}
}

void	extract_line(t_list *stash, char **line)
{
	t_list	*current;
	int		i;
	int		j;
	int		total_len;

	total_len = line_len(stash);
	*line = malloc(sizeof(char) * (total_len + 1));
	current = stash;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->content[i] != '\0')
		{
			(*line)[j] = current->content[i];
			j++;
			if (current->content[i] == '\n')
				break ;
			i++;
		}
		current = current->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*current;
	t_list	*next;

	current = *stash;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*stash = NULL;
}
