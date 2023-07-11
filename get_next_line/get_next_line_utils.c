/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:20:56 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/11 10:51:00 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	add_to_stash(t_list **stash, char *buffer, int bytes_read)
{
	int		i;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list) * 1);
	if (!new_node)
		return (0);
	new_node->content = malloc(sizeof(char) * (bytes_read + 1));
	if (!new_node->content)
	{
		free(new_node);
		return (0);
	}
	i = 0;
	while (i < bytes_read)
	{
		((char *)new_node->content)[i] = buffer[i];
		i++;
	}
	((char *)new_node->content)[i] = '\0';
	add_to_last_node(new_node, stash);
	return (1);
}

void	add_to_last_node(t_list *new_node, t_list **stash)
{
	t_list	*last_node;

	if (*stash == NULL)
		*stash = new_node;
	else
	{
		last_node = *stash;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

int	found_newline(t_list *stash)
{
	t_list	*current;
	char	*content;
	int		i;

	if (stash == NULL)
		return (0);
	current = stash;
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

int	line_len(t_list *stash)
{
	t_list	*current;
	char	*content;
	int		i;
	int		count;

	current = stash;
	count = 0;
	while (current != NULL)
	{
		content = current->content;
		i = 0;
		while (content[i] != '\0')
		{
			count++;
			i++;
			if (content[i] == '\n')
				break ;
		}
		current = current->next;
	}
	return (count);
}
