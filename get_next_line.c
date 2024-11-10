/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:59:10 by mquero            #+#    #+#             */
/*   Updated: 2024/11/09 14:01:05 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t  ft_strlcpy(char *dst, const char *src, size_t size)
{
        size_t  i;
        size_t  len;

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	const char	*s;
	char		*d;

	if (dest == NULL && src == NULL)
		return (dest);
	i = 0;
	d = dest;
	s = src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*des;

	len = 0;
	while (s[len])
		len++;
	des = (char *)malloc((len + 1) * sizeof(char));
	if (des == NULL)
		return (NULL);
	len = 0;
	while (s[len])
	{
		des[len] = s[len];
		len++;
	}
	des[len] = '\0';
	return (des);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = "";
	static int	i = 0;
	char	*line;
	int	k;

	line = NULL;
	k = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (i == 0)
		read(fd, buffer, BUFFER_SIZE);
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		i++;
		k++;
	}
	if (buffer[i] == '\n')
	{
		i++;
		k++;
	}
	line = (char *)malloc(sizeof(char) * (k + 1));
	if (line == NULL)
		return NULL;
	ft_strlcpy(line, (buffer + i - k), (size_t)k + 1);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*next;
	
	fd = open("41_with_nl", O_RDONLY);
	// if (fd == -1)
	//	printf("Error Number");
	next = get_next_line(fd);
	while (next != NULL)
	{
		printf("%s", next);
		free(next);
		next = get_next_line(fd);
	}
	next = get_next_line(fd);
	free(next);
	return (0);
}*/
