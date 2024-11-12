/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:59:10 by mquero            #+#    #+#             */
/*   Updated: 2024/11/11 15:11:16 by mquero           ###   ########.fr       */
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
	char	temp[1024];
	int	i;
	char	*line;
	static int	k = 1;
	static int	j = 0;

	line = NULL;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || k == 0)
		return (NULL);
	while (k != 0)
	{
		if (j == 0)
			k = read(fd, buffer, BUFFER_SIZE);
		while (j < k && buffer[j] != '\n')
		{
			temp[i] = buffer[j];
			i++;
			j++;
		}
		if (buffer[j] == '\n')
			break;
		j = 0;
	}
	if (buffer[j] == '\n' || buffer[j] == '\0')
	{
		temp[i] = buffer[j];
		i++;
		j++;
		line = (char *)malloc(sizeof(char) * (i + 1));
		if (line == NULL)
			return NULL;
		ft_strlcpy(line, (temp), (size_t)i + 1);
		return line;
	}
	return NULL;
}

int	main(void)
{
	int		fd;
	char	*next;
	
	fd = open("./textfiles/41_with_nl", O_RDONLY);
	// if (fd == -1)
	//	printf("Error Number");
	next = get_next_line(fd);	
	while (next != NULL)
	{
		printf("%s", next);
		free(next);
		next = get_next_line(fd);
	}
	return (0);
}
