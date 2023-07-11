#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	add_to_stash(t_list **stash, char *buffer, int bytes_read)
{
	int		i;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list) * 1);
	if (!new_node)
		return (0);
	new_node->content = malloc(sizeof(char) * (bytes_read + 1));
	if (!new_node->content)
	{
		free(new_node);
		return (0);
	}
	i = 0;
	while (i < bytes_read)
	{
		((char *)new_node->content)[i] = buffer[i];
		i++;
	}
	((char *)new_node->content)[i] = '\0';
	add_to_last_node(new_node, stash);
	return (1);
}

void	add_to_last_node(t_list *new_node, t_list **stash)
{
	t_list	*last_node;

	if (*stash == NULL)
		*stash = new_node;
	else
	{
		last_node = *stash;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

int	found_newline(t_list *stash)
{
	t_list	*current;
	char	*content;
	int		i;

	if (stash == NULL)
		return (0);
	current = stash;
	while (current)
	{
		content = current->content;
		i = 0;
		while (content[i] != '\0')
		{
			if (content[i] == '\n')
				return (1);
			i++;
		}
		current = current->next;
	}
	return (0);
}

int	line_len(t_list *stash)
{
	t_list	*current;
	char	*content;
	int		i;
	int		count;

	current = stash;
	count = 0;
	while (current != NULL)
	{
		content = current->content;
		i = 0;
		while (content[i] != '\0')
		{
			count++;
			i++;
			if (content[i] == '\n')
				break ;
		}
		current = current->next;
	}
	return (count);
}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	if (stash == NULL)
		stash = NULL;
	line = NULL;
	read_and_stash(&stash, fd);
	if (stash == NULL)
		return (0);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		clean_stash(&stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(t_list **stash, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	while (!found_newline(*stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && bytes_read == 0) || bytes_read == -1)
			return ;
		buffer[bytes_read] = '\0';
		add_to_stash(stash, buffer, bytes_read);
	}
}

void	extract_line(t_list *stash, char **line)
{
	t_list	*current;
	char	*content;
	int		i;
	int		j;

	if (stash == NULL)
		return ;
	current = stash;
	j = 0;
	*line = malloc(sizeof(char) * (line_len(stash) + 1));
	while (current != NULL)
	{
		content = current->content;
		i = 0;
		while (content[i] != '\0')
		{
			(*line)[j] = content[i];
			i++;
			j++;
			if (content[i] == '\n')
				break ;
		}
		current = current->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*current;
	char	*content;
	char	*new_content;
	int		i;

	new_content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*stash == NULL)
		return ;
	current = *stash;
	while (current->next != NULL)
		current = current->next;
	content = current->content;
	while (*content != '\n')
		content++;
	content++;
	i = 0;
	while (*content != '\0')
	{
		new_content[i++] = *content;
		content++;
	}
	*stash = NULL;
	current->content = new_content;
	*stash = current;
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
		printf("%s\n", line);
		free(line);
	}

	close(fd);
	return (0);
}
