/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:10:57 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/17 23:30:07 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

# endif

/* get_next_line_bonus.c */
char	*get_next_line(int fd);
void	read_and_stash(char **stash, int fd);
void	extract_line(char *stash, char **line);
void	clean_stash(char **stash);

/* get_next_line_utils_bonus.c */
int		found_newline(char *stash);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif
