/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:56:23 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/13 19:05:37 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

/* get_next_line */
char	*get_next_line(int fd);
void	read_and_stash(char **stash, int fd);
void	extract_line(char *stash, char **line);
void	clean_stash(char **stash);

/* get_next_line_utils */
int		ft_strchr(char *str, char c);
char	*ft_strjoin(int len, char *s1, char *s2);
size_t	ft_strlen(char *str);

#endif
