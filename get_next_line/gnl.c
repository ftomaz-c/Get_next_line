#include "get_next_line.h"

int	found_newline(char *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
	{
		free(temp);
		free(s1);
		return (NULL);
	}
	while (s1 != NULL && s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		temp[i++] = s2[j++];
	temp[i] = '\0';
	if (s1)
		free(s1);
	return (temp);
}

int	ft_strlen(char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	read_and_stash(&stash, fd);
	if (!stash)
		return (NULL);
	extract_line(stash, &line);
	if (line[0] == '\0')
	{
		free (stash);
		return (NULL);
	}
	clean_stash(&stash);
	return (line);
}

void	read_and_stash(char **stash, int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(buffer);
		return ;
	}
	while (!found_newline(*stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		*stash = ft_strjoin(*stash, buffer);
	}
	free(buffer);
}

void	extract_line(char *stash, char **line)
{
	size_t	len;
	size_t	new_line;
	size_t	i;

	len = ft_strlen(stash);
	*line = malloc(sizeof(char) * (len + 1));
	if (!(*line))
	{
		free(*line);
		*line = NULL;
		return ;
	}
	new_line = 0;
	while (stash[new_line] != '\n' && stash[new_line] != '\0')
		new_line++;
	if (stash[new_line] == '\n')
		new_line++;
	i = 0;
	while (i < new_line)
	{
		(*line)[i] = stash[i];
		i++;
	}
	(*line)[i] = '\0';
}

void	clean_stash(char **stash)
{
	size_t	new_line;
	char	*temp;
	size_t	len;
	int		i;

	new_line = 0;
	while ((*stash)[new_line] != '\n' && (*stash)[new_line] != '\0')
		++new_line;
	if ((*stash)[new_line] == '\n')
		new_line++;
	len = ft_strlen(*stash) - new_line;
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp || len == 0)
	{
		free(temp);
		free(*stash);
		*stash = NULL;
		return ;
	}
	i = 0;
	while ((*stash)[new_line] != '\0')
		temp[i++] = (*stash)[new_line++];
	temp[i] = '\0';
	free(*stash);
	*stash = temp;
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd;
	char *line;

	fd = open("read_error.txt", O_RDWR);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
