/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:19:53 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/10 04:36:06 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = NULL;
	line = NULL;
	read_and_stash(&stash, fd);
	extract_line(&stash, &line);
	clean_stash(&stash);
	//return line or handle end of file
	return (line);
}

void	read_and_stash(t_list **stash, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	while (!found_newline(*stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		add_to_stash(stash, buffer, bytes_read);
	}
}

void	extract_line(t_list **stash, char **line)
{
	t_list	*current;
	char	*content;
	int		i;
	int		j;

	if (*stash == NULL)
		return ;
	current = *stash;
	j = 0;
	*line = malloc(sizeof(char) * (line_len(stash) + 1));
	while (current != NULL)
	{
		content = current->content;
		i = 0;
		while (content[i] != '\0')
		{
			(*line)[j] = content[i];
			i++;
			j++;
			if (content[i] == '\n')
				break ;
		}
		current = current->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*current;
	t_list	*next;
	char	*content;

	if (*stash == NULL)
		return ;
	current = *stash;
	while (current->next != NULL)
	{
		next = current->next;
		content = current->content;
		free(content);
		free(current);
		current = next;
	}
}
