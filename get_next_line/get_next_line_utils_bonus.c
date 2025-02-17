/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:10:59 by ftomaz-c          #+#    #+#             */
/*   Updated: 2025/01/08 12:49:38 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
	{
		free(s1);
		return (NULL);
	}
	while (s1 != NULL && s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		temp[i++] = s2[j++];
	temp[i] = '\0';
	if (s1)
		free(s1);
	return (temp);
}

int	ft_strlen(char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}
