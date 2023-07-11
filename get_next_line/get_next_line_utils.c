/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:52:30 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/11 22:56:55 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *stash)
{
	t_list	*current;
	char	*content;

	current = stash;
	while (current)
	{
		content = current->content;
		while (*content != '\0')
		{
			if (*content == '\n')
				return (1);
			content++;
		}
		current = current->next;
	}
	return (0);
}

void	add_to_stash(t_list **stash, char *buffer, int bytes_read)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*content;

	new_node = malloc(sizeof(t_list));
	new_node->content = malloc(sizeof(char) * (bytes_read + 1));
	content = new_node->content;
	while (*buffer != '\0')
	{
		*content = *buffer;
		content++;
		buffer++;
	}
	*content = '\0';
	new_node->next = NULL;
	if (!(*stash))
	{
		*stash = new_node;
		return ;
	}
	last_node = *stash;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
}

int	line_len(t_list *stash)
{
	t_list	*current;
	char	*content;
	int		count;

	count = 0;
	current = stash;
	while (current)
	{
		content = current->content;
		while (*content != '\0')
		{
			count++;
			if (*content == '\n')
				return (count);
			content++;
		}
		current = current->next;
	}
	return (count);
}
