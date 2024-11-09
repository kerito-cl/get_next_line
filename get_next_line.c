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
	static char	**split = NULL;
	static char	buffer[BUFFER_SIZE] = "";
	static int	i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (i == 0)
	{
		read(fd, buffer, BUFFER_SIZE);
		split = ft_split(buffer, '\n');
	}
	if (split == NULL)
		return (NULL);
	i++;
	if (split[i - 1] != NULL)
		return (split[i - 1]);
	else
	{
		freesplit(split);
		return (NULL);
	}
}

int	main(void)
{
	int		fd;
	char	*next;

	fd = open("test.txt", O_RDONLY);
	// printf("fd = %d\n", fd);
	// if (fd == -1)
	//	printf("Error Number");
	next = get_next_line(fd);
	while (next != NULL)
	{
		printf("%s\n", next);
		next = get_next_line(fd);
	}
	return (0);
}
