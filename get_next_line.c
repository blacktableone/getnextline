/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisu <nisu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:43:36 by zuzu              #+#    #+#             */
/*   Updated: 2026/02/20 23:07:09 by nisu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_save(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*ft_extract_line(char *saved)
{
	size_t	i;
	char	*line;

	if (!saved || !saved[0])
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	line = (char *)malloc(i + 1 + (saved[i] == '\n'));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save_rest(char *saved)
{
	char	*new_saved;
	size_t	i;
	size_t	j;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = (char *)malloc(ft_strlen(saved) - i);
	if (!new_saved)
	{
		free(saved);
		return (NULL);
	}
	i++;
	j = 0;
	while (saved[i])
		new_saved[j++] = saved[i++];
	new_saved[j] = '\0';
	free(saved);
	return (new_saved);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = ft_read_and_save(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_extract_line(saved);
	saved = ft_save_rest(saved);
	return (line);
}
// int	main(void)
// {
// 	//char	*saved = NULL;
// 	int fd = open("test.txt", O_RDONLY);

// 	if (fd == -1)
// 	{
// 		perror("Open failed");
// 		return (1);
// 	}
// 	//test ft_read_and_save
// 	saved = ft_read_and_save(fd, saved);
// 	printf("read and save: %s\n", saved);
// 	free(saved);
// 	char	*line = NULL;
// 	//test ft_extract_line
// 	saved = ft_read_and_save(fd, saved);
// 	line = ft_extract_line(saved);
// 	printf("line: %s\n", line);
// 	free(saved);
// 	free(line);
// 	//test ft_save_rest
// 	saved = ft_read_and_save(fd, saved);
// 	line = ft_extract_line(saved);
// 	saved = ft_save_rest(saved);
// 	printf("save rest: %s\n", saved);
// 	free(saved);
// 	free(line);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("get_next_line: %s", line);
// 		free(line); // what time need to use free?
// 	}
// 	close(fd);
// 	return (0);
// }
