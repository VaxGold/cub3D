/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:00:15 by omercade          #+#    #+#             */
/*   Updated: 2020/02/17 16:57:03 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_file(char *buff, char **s, int fd)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = *s;
		*s = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
		if (ft_strtab(*s) != -1)
			break ;
	}
	return (ret);
}

int		record_line(char **line, char **s, int ret)
{
	char *tmp;

	if (ret == 0)
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	*line = ft_substr(*s, 0, ft_strtab(*s));
	tmp = *s;
	*s = ft_substr(tmp, ft_strtab(tmp) + 1,
		ft_strlen(tmp) - ft_strtab(tmp));
	free(tmp);
	tmp = NULL;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	static char	*s;
	char		*buff;

	if ((buff = malloc(BUFFER_SIZE + 1)) == NULL)
		return (-1);
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || read(fd, buff, 0) == -1)
	{
		free(buff);
		buff = NULL;
		return (-1);
	}
	if (s == NULL)
		s = ft_strdup("");
	if (ft_strtab(s) == -1)
		ret = read_file(buff, &s, fd);
	else
		ret = ft_strtab(s) + 1;
	free(buff);
	return (record_line(line, &s, ret));
}
