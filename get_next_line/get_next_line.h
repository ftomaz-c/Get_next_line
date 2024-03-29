/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:39:52 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/17 17:51:25 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000000

# endif

/* get_next_line.c */
char	*get_next_line(int fd);
void	read_and_stash(char **stash, int fd);
void	extract_line(char *stash, char **line);
void	clean_stash(char **stash);

/* get_nex_line_utils.c */
int		found_newline(char *stash);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif
