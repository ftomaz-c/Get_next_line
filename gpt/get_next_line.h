
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

char *get_next_line(int fd);
int read_data(int fd, char *buffer, int *stash_index, int *bytes_read);
Node* append_node(Node *line_head, Node **line_tail, char c);
int count_line_length(Node *line_head);
void copy_line_to_array(Node *line_head, char *line);

#endif
