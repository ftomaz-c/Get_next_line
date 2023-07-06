/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:21:09 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/06 01:08:10 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct s_list
{
	void			*content;
	struct t_list	*next;
}					t_list;

char 	*get_next_line(int fd);
int		found_newline(t_list *stash);
int		add_to_stash(t_list **stash, char *buffer, int bytes_read);

#endif
