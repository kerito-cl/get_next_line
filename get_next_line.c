/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:59:10 by mquero            #+#    #+#             */
/*   Updated: 2024/11/14 16:45:05 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_when_nl(char *temp, char *buffer, t_myitems *mystruct, int hold)
{
	if (mystruct->i == 0)
		temp = ft_strjoin(temp, buffer, mystruct->j + 1);
	else
		temp = ft_strjoin(temp, buffer + hold, mystruct->j - hold + 1);
	mystruct->j = mystruct->j + 1;
	mystruct->i = 1;
	return (temp);
}

char	*check_when_no_nl(char *temp, char *buffer, t_myitems *mystruct,
		int hold)
{
	if (mystruct->i == 1)
	{
		temp = ft_strjoin(temp, buffer + hold, mystruct->j - hold);
		mystruct->i = 0;
	}
	else
	{
		temp = ft_strjoin(temp, buffer, mystruct->j);
		mystruct->i = 0;
	}
	return (temp);
}

char	*read_line(int fd, char *temp, char *buffer, int hold)
{
	static t_myitems	mystruct = {0, 1};
	static int			k = 1;

	hold = mystruct.j;
	while (k > 0)
	{
		if (mystruct.j == k && mystruct.i == 0)
		{
			mystruct.j = 0;
			k = read(fd, buffer, BUFFER_SIZE);
			if (hold > 0 && k == 0 && mystruct.i != 1 && temp[0] != '\0')
				return (temp);
		}
		while (mystruct.j < k)
		{
			if (buffer[mystruct.j] == '\n')
				return (check_when_nl(temp, buffer, &mystruct, hold));
			mystruct.j++;
		}
		if (mystruct.j == k && k > 0)
			temp = check_when_no_nl(temp, buffer, &mystruct, hold);
	}
	free(temp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*temp;
	char		*line;
	int			hold;
	static char	buffer[BUFFER_SIZE] = "";

	hold = 0;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (temp == NULL)
		return (NULL);
	line = read_line(fd, temp, buffer, hold);
	if (line != NULL)
		return (line);
	return (NULL);
}
