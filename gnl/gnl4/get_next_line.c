#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int stash_index = 0;
    static int bytes_read = 0;
    Node *line_head = NULL;
    Node *line_tail = NULL;
    int line_length;
    char *line;

    while (1)
    {
        int c;
        if (!read_data(fd, buffer, &stash_index, &bytes_read))
            break;

        c = buffer[stash_index++];
        if (c == '\n')
            break;

        line_head = append_node(line_head, &line_tail, c); // Pass the address of line_tail using the &
        if (line_head == NULL)
            return NULL;
    }
    if (bytes_read <= 0 && line_head == NULL)
        return NULL;
    line_length = count_line_length(line_head);
    line = (char *)malloc(line_length + 1);
    if (line == NULL)
        return NULL;
    copy_line_to_array(line_head, line);
    return line;
}


int	main()
{
	int fd;
	char *line;

	fd = open("hp1.txt", O_RDONLY);
 	/* printf("%s\n", get_next_line(fd)); */
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
