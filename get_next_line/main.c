/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:52:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/05 23:57:23 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int	main(void)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	fd = open("hp1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("\033[31mError opening the file.\033[0m\n");
		return (1);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE-1);
	if (bytes_read == -1)
	{
		printf("\033[31mError reading the file.\033[0m\n");
		close(fd);
		return (1);
	}
	buffer[bytes_read] = '\0';
	printf("\033[34mFILE CONTENT:\033[0m\n%s\n", buffer);
	close(fd);
	return (0);
}
