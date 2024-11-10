/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:40:11 by mquero            #+#    #+#             */
/*   Updated: 2024/11/09 14:02:33 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

void	freesplit(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	countarr(int n, const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i + 1] == '\0')
			n++;
		i++;
	}
	return (n);
}

static char	*allocate(char const *s, char c, int *y)
{
	int		k;
	char	*temp;

	k = 0;
	while (s[*y] != c && s[*y] != '\0')
	{
		k++;
		*y = *y + 1;
	}
	*y = *y + 1;
	k++;
	temp = (char *)malloc((k + 2) * (sizeof(char)));
	if (temp == NULL)
		return (NULL);
	ft_strlcpy(temp, (s + *y - k), k + 1);
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**strsplit;
	int		n;
	int		i;
	int		y;

	i = 0;
	n = 0;
	y = 0;
	n = countarr(n, s, c);
	strsplit = (char **)malloc((n + 1) * sizeof(char *));
	if (strsplit == NULL)
		return (NULL);
	strsplit[n] = NULL;
	while (i < n)
	{
		strsplit[i] = allocate((char *)s, c, &y);
		if (strsplit[i] == NULL)
		{
			freesplit(strsplit);
			return (NULL);
		}
		i++;
	}
	return (strsplit);
}*/
