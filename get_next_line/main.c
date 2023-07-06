/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:52:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/06 18:00:57 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;

	fd = open("../hp1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("\033[31mError opening the file.\033[0m\n");
		return (1);
	}
	get_next_line(fd);
	close(fd);
	return (0);
}
