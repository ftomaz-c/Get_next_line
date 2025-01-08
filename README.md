# Get Next Line (GNL)
A robust implementation of the `get_next_line` function, designed to read a line from a file descriptor, including support for multiple file descriptors. This project demonstrates advanced memory management and file handling techniques in C.

---

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Function Prototype](#function-prototype)
- [How It Works](#how-it-works)
- [Usage](#usage)
- [Multi-FD Support](#multi-fd-support)
- [Limitations](#limitations)
- [Compilation](#compilation)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

---

## Overview
The `get_next_line` function reads a single line (terminated by a newline or EOF) from a file descriptor. This implementation:
- Handles arbitrarily large lines.
- Supports multiple open file descriptors.
- Demonstrates clean memory management.

### Project Objective
This project was developed as part of the 42 School curriculum, showcasing mastery in low-level file I/O operations and dynamic memory management in C.

---

## Features
- **Dynamic Buffer Allocation**: Handles lines of any length dynamically without memory overflow.
- **Multi-FD Support**: Works seamlessly with multiple file descriptors simultaneously.
- **Error Handling**: Gracefully handles errors like invalid file descriptors or failed `read` calls.
- **Custom String Library**: Includes helper functions like `ft_strjoin` and `ft_strlen`.

---

## Function Prototype  
```c
char *get_next_line(int fd);
```

## Parameters
- `fd`: File descriptor to read from.

## Return Value
- line: A `NULL`-terminated string containing the get next line, including the newline character (if present).
- NULL: On EOF, error, or if the buffer size is invalid

---

## How It Works
1. Static Buffer: Uses a static variable (or an array for multi-FD) to retain leftover data across calls.
2. Reading the File: Reads chunks of BUFFER_SIZE bytes until a newline or EOF is encountered.
3. Extracting the Line: Separates the line from the static buffer while retaining leftover data for subsequent calls.
4. Memory Management: Dynamically allocates memory for lines and handles cleanup when the file ends or errors occur.

---

## Usage
### Code Example
```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int fd = open("example.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

## Expected Output
For an `example.txt` file containing:
```bash
Hello, World!
This is a test.
```
The output would be:
```bash
Hello, World!
This is a test.
```

---

## Multi-FD Support (Bonus)
The implementation supports multiple file descriptors using a static array:
```c
static char *stash[1024];
```
Each file descriptor has its own stash, allowing simultaneous reads from different files or inputs.

## Limitations
- BUFFER_SIZE: Must be defined as a positive integer.
- File Descriptors: Limited to 1024 (or RLIMIT_NOFILE) in this implementation.
- Error Handling: Relies on the caller to free resources (e.g., lines returned).

---

## Compilation
### Files Required
- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### Compile with `BUFFER_SIZE`
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

---

## Testing
### Basic Test
Use the provided `main.c` file or write your own to test:
```bash
./gnl
```

### Multi-FD Test
```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
```