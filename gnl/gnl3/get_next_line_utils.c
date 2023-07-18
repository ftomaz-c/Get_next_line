/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:42:22 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/07/12 18:28:59 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *stash)
{
	while (*stash != '\0')
	{
		if (*stash == '\n')
			return (1);
		stash++;
	}
	return (0);
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
