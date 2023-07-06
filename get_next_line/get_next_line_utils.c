/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:20:56 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/06 18:00:30 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	add_to_stash(t_list **stash, char *buffer, int bytes_read)
{
	int		i;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = malloc(sizeof(char ) * (bytes_read + 1));
	if (!new_node->content)
	{
		free(new_node);
		return (0);
	}
	i = 0;
	while (i < bytes_read)
	{
		((char *)new_node->content)[i] = buffer[i];
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	((char *)new_node->content)[i] = '\0';
	new_node->next = *stash;
	*stash = new_node;
	return (1);
}

int		found_newline(t_list **stash)
{
	t_list	*current;
	char *content;
	int	i;

	current = *stash;
	while (current)
	{
		content = current->content;
		i = 0;
		while (content[i] != '\0')
		{
			if (content[i] == '\n')
				return (1);
			i++;
		}
		current = current->next;
	}
	return (0);
}
