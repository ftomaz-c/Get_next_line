#include "get_next_line.h"

int read_data(int fd, char *buffer, int *stash_index, int *bytes_read)
{
    if (*stash_index >= *bytes_read)
    {
        *bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (*bytes_read <= 0)
            return 0;
        buffer[*bytes_read] = '\0';
        *stash_index = 0;
    }
    return 1;
}

Node* append_node(Node *line_head, Node **line_tail, char c)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;

    new_node->data = c;
    new_node->next = NULL;

    if (line_head == NULL)
    {
        line_head = new_node;
        *line_tail = new_node;  // Update line_tail using the double pointer
    }
    else
    {
        (*line_tail)->next = new_node;  // Dereference line_tail to update its next pointer
        *line_tail = new_node;  // Update line_tail using the double pointer
    }
    return line_head;
}

int count_line_length(Node *line_head)
{
    int line_length = 0;
    Node *current = line_head;
    while (current != NULL)
    {
        line_length++;
        current = current->next;
    }
    return line_length;
}

void copy_line_to_array(Node *line_head, char *line)
{
    int index;
    Node *current = line_head;
    for (index = 0; current != NULL; index++)
    {
        line[index] = current->data;
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    line[index] = '\0';
}
