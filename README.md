*This project has been created as part of the 42 curriculum by nisu*

# Get Next Line

## Description
The goal is to implement a function that reads one line at a time from a file descriptor, each time it is called. A "line" is defined as a sequence of characters ending with a newline character (\n), or the end of file if no newline is present.

The core challenge is that the low-level read() system call does not understand the concept of a "line" — it reads a fixed number of bytes at a time, determined by BUFFER_SIZE. The function must therefore accumulate data across multiple calls to read(), detect when a full line is available, return exactly that line, and remember any leftover data for the next call.

### Overview
The function signature is:
`char *get_next_line(int fd);`

It returns the next line (including the \n if present) each time it is called, and returns NULL when the file has been fully read or an error occurs. The caller is responsible for freeing the returned string.

The algorithm is built around a single static variable called saved, which acts as a persistent buffer between function calls. This is the key insight of the project: because static variables retain their value between calls, saved can hold whatever data was read from the file but not yet returned to the caller.

- Step 1 — Fill the buffer (ft_read_and_save)
The function calls read() in a loop, appending each chunk of data to saved using ft_strjoin. The loop continues until either a newline character is found in saved (meaning at least one complete line is ready), or read() returns 0 (end of file). The old saved is freed on every iteration by ft_strjoin to prevent memory leaks.

- Step 2 — Extract the line (ft_extract_line)
Once saved contains a newline (or the end of file), ft_extract_line scans saved to find the first \n, then allocates a new string containing everything from the start up to and including that \n. If no \n is found (last line of file), it returns just the remaining content without a newline. This function does not modify saved.

- Step 3 — Save the remainder (ft_save_rest)
After extracting the line, ft_save_rest creates a new string containing everything in saved after the \n, frees the old saved, and returns the new remainder. If nothing remains after the \n, it frees saved and returns NULL, resetting the static buffer cleanly.

## Instructions

### Files
- get_next_line.c — main function and helper functions
- get_next_line_utils.c — ft_strlen, ft_strchr, ft_strjoin
- get_next_line.h — header file with prototypes and BUFFER_SIZE definition

### Compilation
**Compile with a custom BUFFER_SIZE using the -D flag:**
```shell
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
./gnl
```

**To test:**
make txt file:
```shell
printf "\n\n\n" > filename.txt
```
verfy the file:
```shell
cat -e filename.txt
```

Usage Example
make main.c for testing:
```c
#include <stdio.h>    // For printf
#include <fcntl.h>    // For open() and O_RDONLY
#include <stdlib.h>   // For free()
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;
    int     count = 1;

    fd = open("only_nl.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: [%s]\n", count, line);
        free(line);
        count++;
    }
    printf("Line %d: [%s] (End of File)\n", count, line);
    close(fd);
    return (0);
}
```

```shell
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl
```


**Important: always free the returned line after each call. The caller owns the memory.**

## Resources
- [A general gitbook by Laura & Simon, from Switzerland (42 Lausanne)](https://42-cursus.gitbook.io/guide)

### AI Usage
Claude (claude.ai) was used to:
- Generate this `README.md` based on the project's source code and the 42 README requirements.
- Better understand the concept

