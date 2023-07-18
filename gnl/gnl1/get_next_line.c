/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:19:53 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/11 22:17:50 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	if (stash == NULL)
		stash = NULL;
	line = NULL;
	read_and_stash(&stash, fd);
	if (stash == NULL)
		return (0);
	extract_line(stash, &line);
	if (line[0] == '\0')
	{
		stash = NULL;
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
	char	*content;
	t_list	*current;

	while (!found_newline(*stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*stash)
		{
			current = *stash;
			content = current->content;
			if ((*content == '\0' && bytes_read == 0) || bytes_read == -1)
				return ;
		}
		buffer[bytes_read] = '\0';
		add_to_stash(stash, buffer, bytes_read);
	}
}

void	extract_line(t_list *stash, char **line)
{
	t_list	*current;
	int		i;
	int		j;

	if (stash == NULL)
		return ;
	current = stash;
	j = 0;
	*line = malloc(sizeof(char) * (line_len(stash) + 1));
	while (current != NULL)
	{
		i = 0;
		while ((current->content)[i] != '\0')
		{
			(*line)[j] = (current->content)[i];
			j++;
			if ((current->content)[i] == '\n')
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
	char	*new_content;
	int		i;

	new_content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*stash == NULL)
		return ;
	current = *stash;
	while (current->next != NULL)
		current = current->next;
	while (*(current->content) != '\n')
		(current->content)++;
	(current->content)++;
	i = 0;
	while (*(current->content) != '\0')
	{
		new_content[i++] = *(current->content);
		(current->content)++;
	}
	*stash = NULL;
	current->content = new_content;
	*stash = current;
}
