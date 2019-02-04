/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanouji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 01:35:14 by mzanouji          #+#    #+#             */
/*   Updated: 2018/12/16 03:34:09 by mzanouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fjoin(char *s1, char *s2, int carac)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s2[len] != '\0')
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (i + len + 1))))
		return (NULL);
	i = -1;
	len = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[++len] != '\0')
		str[i + len] = s2[len];
	str[i + len] = '\0';
	if (carac != 0)
		free(s1);
	return (str);
}

int		ft_searchn(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (-1);
	else
		return (i);
}

char	*ft_leftover(char *ptr)
{
	int		i;
	int		len;
	char	*nextline;

	i = 0;
	len = -1;
	if (ft_searchn(ptr) != -1)
	{
		free(ptr);
		return ("\0");
	}
	while (ptr[++len] != '\0')
		if (ptr[i] != '\n' && ptr[len] == '\n')
			i = len;
	if (!(nextline = (char*)malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	len = 0;
	while (ptr[i] != '\0')
		nextline[len++] = ptr[++i];
	nextline[len] = '\0';
	free(ptr);
	return (nextline);
}

char	*ft_firstline(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	while (ptr[i] != '\0' && ptr[i] != '\n')
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (ptr[i] != '\0' && ptr[i] != '\n')
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	char		*buff;
	static char	*ptr = "\0";
	int			byte;
	int			carac;

	carac = 0;
	byte = 0;
	if (!line || fd < 0 || BUFF_SIZE <= 0 ||
		!(buff = malloc(sizeof(char) * BUFF_SIZE + 1)) || read(fd, buff, 0) < 0)
		return (-1);
	while (ft_searchn(ptr) != -1 && (byte = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[byte] = '\0';
		ptr = ft_fjoin(ptr, buff, carac++);
	}
	if (carac == 0)
	{
		ptr = ft_fjoin(ptr, "\0", 0);
		carac = ft_searchn(ptr);
	}
	*line = ft_firstline(ptr);
	ptr = ft_leftover(ptr);
	free(buff);
	return ((carac != 0 || byte > 0) ? 1 : byte);
}
