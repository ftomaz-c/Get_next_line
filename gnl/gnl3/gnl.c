#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int found_newline(char *stash)
{
	while (stash)
	{
		if (stash == '\n')
			return 1;
		stash++;
	}
	return 0;
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		s1_len;
	int		s2_len;
	int		new_s_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s_len = s1_len + s2_len + 1;
	new_s = malloc(sizeof(char) * new_s_len);
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, s1_len + 1);
	ft_strlcat(new_s, s2, new_s_len);
	return (new_s);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	src_len;
	unsigned int	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	j = dst_len;
	if (size == 0 || size <= dst_len)
		return (src_len + size);
	while (src[i] && (i < size - dst_len - 1))
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (src_len + dst_len);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_stash(&stash, fd);
	if (!stash)
		return (NULL);
	extract_line(stash, &line);
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	clean_stash(&stash);
	return (line);
}
void read_and_stash(char **stash, int fd)
{
	int bytes_read;
	char *buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!found_newline(*stash))
	{
		if (!buffer)
		{
			free(buffer);
			return ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		ft_strjoin(*stash, buffer);
	}
	free(buffer);
}

void	extract_line(char *stash, char	**line)
{
	size_t	len;

	len = ft_strlen(stash);
	*line = malloc(sizeof(char) * len + 1);
	if (!line)
	{
		free (line);
		return ;
	}
	ft_strjoin(stash, *line);
	return ;
}

void clean_stash(char **stash)
{
	char *temp;
	size_t len;

	len = ft_strlen(*stash);
	temp = malloc(sizeof(char) * len);
	if (!temp)
	{
		free(temp);
		return ;
	}
	while (*stash != '\n')
		(*stash)++;
	(*stash)++;
	while (*stash != '\0')
		*temp++ = *(*stash)++;
	*temp = '\0';
	*stash = temp;
}


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
