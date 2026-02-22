*This project has been created as part of the 42 curriculum by nisu*

# Get Next Line

## Description
The goal is to implement a function that reads one line at a time from a file descriptor, each time it is called. A "line" is defined as a sequence of characters ending with a newline character (\n), or the end of file if no newline is present.

The core challenge is that the low-level read() system call does not understand the concept of a "line" — it reads a fixed number of bytes at a time, determined by BUFFER_SIZE. The function must therefore accumulate data across multiple calls to read(), detect when a full line is available, return exactly that line, and remember any leftover data for the next call.

### Algorithm Explanation
The function signature is:
`char *get_next_line(int fd);`

The underlying mechanism of this get_next_line implementation relies on a single static variable (`static char *saved`) and a three-step algorithmic approach:

- Step 1 — Fill the buffer (`ft_read_and_save`)
The function allocates a temporary `buffer` of `BUFFER_SIZE`. It uses a `while` loop to `read()` from the file descriptor into this buffer. After each read, it appends (using `ft_strjoin`) the newly read buffer to the static saved string. The loop stops as soon as a newline character (`\n`) is detected in the `saved` string, or if `read()` returns `0` (EOF).

- Step 2 — Extract the line (`ft_extract_line`)
Once a newline is found (or EOF is reached), the code iterates through the `saved` string to find the exact length of the current line (up to and including the `\n`). It dynamically allocates memory for this exact length, copies the characters over, and null-terminates it. This is the string that will be returned to the user.

- Step 3 — Save the remainder (`ft_save_rest`)
Because a single `read()` might fetch characters that belong to the next line (especially if `BUFFER_SIZE` is large), those extra characters cannot be lost. The function isolates everything after the `\n` in the old `saved` string, allocates a new string for this remainder, frees the old `saved` string, and assigns the new remainder back to the `saved` static pointer.

### Justification
This approach was selected because it efficiently handles the unpredictability of `BUFFER_SIZE`.

- If `BUFFER_SIZE` is massive (e.g., 9999), the static variable safely caches all the excess data so subsequent calls to `get_next_line` don't need to trigger the `read()` system call until the cache is empty.

If `BUFFER_SIZE` is tiny (e.g., 1), the algorithm loops and dynamically expands the static variable character-by-character without losing data.


## Instructions

### Files
- get_next_line.c — main function and helper functions
- get_next_line_utils.c — ft_strlen, ft_strchr, ft_strjoin
- get_next_line.h — header file with prototypes and BUFFER_SIZE definition

### test
**make txt file:**
- `-n` means No trailing newline ,prevents the system from automatically adding a newline character at the end.
- `-e` means Enable interpretation of escapes It tells the system: "If you see special characters such as \n or \t in the string, please translate them into actual newline and tab characters, and do not print them as ordinary letters!"

```shell
echo -n "" > empty.txt
echo -e "\n\n\n" > only_nls.txt
echo -n "No newline at the end" > no_nl.txt
echo -e "Line 1\nLine 2\nLine 3" > normal.txt
```
**verfy the file:**
```shell
cat -e filename.txt
```

**Usage Example**
make main.c for testing:
```c
#include <stdio.h>    // For printf
#include <fcntl.h>    // For open() and O_RDONLY
#include <stdlib.h>   // For free()
#include "get_next_line.h"

void test_file(char *filename)
{
    int fd;
    char *line;
    int line_count = 1;

    printf("\n--- test file: %s ---\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("fail to open\n");
        return;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d : %s", line_count++, line);
        free(line); // // Don't forget to free the line after using it!
    }
    close(fd);
    printf("\n--- EOF ---\n");
}

int main(void)
{
    test_file("empty.txt");
    test_file("only_nls.txt");
    test_file("no_nl.txt");
    test_file("normal.txt");
    
    printf("\n--- Testing Invalid FD (-1) ---\n");
    char *err_line = get_next_line(-1);
    if (!err_line)
        printf("Correctly returned NULL.\n");
        
    return (0);
}
```

### Compilation
Compile the code with the `-D BUFFER_SIZE=n` flag, where `n` is the number of bytes read at a time.
```bash
# Compile the code (change the value of BUFFER_SIZE, such as 1, 10, 42, 9999)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Use Valgrind to check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```



## Resources
- [A general gitbook by Laura & Simon, from Switzerland (42 Lausanne)](https://42-cursus.gitbook.io/guide)

### AI Usage
Claude (claude.ai) was used to:
- Generate this `README.md` based on the project's source code and the 42 README requirements.
- Better understand the concept

