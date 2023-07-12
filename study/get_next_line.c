/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:55:33 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/12 18:03:02 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	buffer = malloc()
	read(fd, buffer, BUFFER_SIZE);
}


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int		main()
{
	int		fd;
	char	*line;

	fd = fopen("hp1.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}
