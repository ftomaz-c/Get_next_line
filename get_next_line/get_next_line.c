/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:19:53 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/06/06 16:53:41 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	int				readed;

	stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	readed = 1;
	line = NULL;
	read_and_stash(&stash, fd, &readed);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	// 3. clean stash;
	return (line);
}

void	read_and_stash(t_list **stash, int fd, int *readed_ptr)
{
	char	*buf;

	while (!found_newline(*stash) && *readed_ptr != 0)
	{
		buf = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		*readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && *readed_ptr == 0) || *readed_ptr == -1)
		{
			free (buf);
			return ;
		}
		buf[*readed_ptr] = '\0';
		add_to_stash(stash, buf, *readed_ptr);
		free (buf);
	}
}

void	add_to_stash(t_list **stash, char *buf, int *readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	i = 0;
	new_node->next = NULL;
	new_node = malloc(sizeof(char *) * (*readed + 1));
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = lst_get_last(*stash);
	last->next = new_node;
}

extract_line(t_list *stash, char *line)
{

}
