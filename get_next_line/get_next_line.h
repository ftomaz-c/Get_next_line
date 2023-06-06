/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:21:09 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/06/06 16:53:45 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct t_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	read_and_stash(t_list **stash, int fd, int *readed_ptr);
int		found_newline(t_list *stash);
t_list	*lst_get_last(t_list *stash);

#endif
