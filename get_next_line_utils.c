/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisu <nisu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 02:41:51 by zuzu              #+#    #+#             */
/*   Updated: 2026/02/21 17:22:50 by nisu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == '\0' && (char)c == '\0')
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			new_str[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			new_str[j++] = s2[i++];
	new_str[j] = '\0';
	free(s1);
	return (new_str);
}
// int	main(void)
// {
// 	char	*s1 = strdup("1234");
// 	char	*s2 = "abc";
// 	printf("s len is %zu.\n",ft_strlen(s1));
// 	printf("%s.\n",ft_strchr(s1, '2'));
// 	printf("%s.\n",ft_strjoin(s1, s2));

// }
