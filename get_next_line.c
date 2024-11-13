/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:59:10 by mquero            #+#    #+#             */
/*   Updated: 2024/11/13 19:03:34 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			i;
	const char	*s;
	char		*d;

	if (dest == NULL && src == NULL)
		return (dest);
	i = 0;
	d = dest;
	s = src;
	while (i < (int)n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}


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

char	*ft_strdup(const char *s, size_t n)
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
	while (len < n && s[len])
	{
		des[len] = s[len];
		len++;
	}
	des[len] = '\0';
	return (des);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}


char	*resize_buffer(char *temp, int *capacity)
{
	char	*newtemp;
	int	oldcapacity;

	oldcapacity = *capacity;
	*capacity = *capacity * 2;
	newtemp = (char *)malloc(sizeof(char) * (*capacity));
	ft_strlcpy(newtemp, temp, oldcapacity + 1);
	free(temp);
	return (newtemp);

}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		n;

	if (nmemb && size > (size_t)-1 / nmemb
		&& nmemb && size > (size_t)-1 / size)
		return (0);
	n = nmemb * size;
	ptr = malloc(n);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, n);
	return (ptr);
}


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	*ft_strjoin(char *s1, char const *s2, size_t n)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j < n)
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(s1);
	return (dest);
}


char	*read_line(int fd, char *temp)
{
	static char	buffer[BUFFER_SIZE] = "";
	static int	k = 1;
	static int	j = 0;
	static int	i = 0;
	static int	flag = 0;

	while (k > 0)
	{
		if (flag == 1)
		{
			temp = ft_strjoin(temp, buffer + j, j + 1);
			i = 0;
			j = 0;
			flag = 0;
			return temp;
		}
		if (i == 0)
		{
			k = read(fd, buffer, BUFFER_SIZE);
			if (k < BUFFER_SIZE)
				ft_bzero(buffer + k, k);
		}
		while (j < k)
		{
			if (buffer[j] == '\n' || k  == '\0')
			{
				temp = ft_strjoin(temp, buffer, j + 1);
				j++;
				i = 1;
				flag = 1;

				//printf("%s", temp);
				return (temp);
			}
			j++;
		}
		if (j == k && flag == 0 && k != 0)
		{
			temp = ft_strjoin(temp, buffer, k);
			i = 0;
			j = 0;
		}
	}
	free(temp);
	return NULL;
}

char	*get_next_line(int fd)
{
	char	*temp;
	char	*line;
	
	temp = (char *)ft_calloc( BUFFER_SIZE + 1, sizeof(char));
	if (temp == NULL)
		return (NULL);
	temp = read_line(fd, temp);
	if (temp != NULL)
		return temp;
	free(temp);
	return NULL;
}

int	main(void)
{
	int		fd;
	char	*next;
	
	fd = open("./textfiles/test.txt", O_RDONLY);
	// if (fd == -1)
	//	printf("Error Number");
	next = get_next_line(fd);
	while (next != NULL)
	{
		printf("%s", next);
		free(next);
		next = get_next_line(fd);
	}
	printf("%s", next);
	free(next);

	return (0);
}
