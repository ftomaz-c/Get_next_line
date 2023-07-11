/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:21:09 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/10 17:42:27 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	read_and_stash(t_list **stash, int fd);
int		add_to_stash(t_list **stash, char *buffer, int bytes_read);
void	add_to_last_node(t_list *new_node, t_list **stash);
int		found_newline(t_list *stash);
void	extract_line(t_list **stash, char **line);
void	clean_stash(t_list **stash);
int		line_len(t_list **stash);

#endif
