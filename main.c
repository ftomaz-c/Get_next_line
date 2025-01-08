/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:52:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2025/01/08 12:38:16 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line/get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("hp1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("\033[31mError opening the file.\033[0m\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
