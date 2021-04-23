/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:06:40 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 21:14:55 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	save_map(t_data *gd, t_check *this, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (this->init_m == 0)
	{
		this->first = ft_lstnew(ft_strdup(line));
		this->init_m = 1;
		gd->map_w = len;
	}
	else
	{
		ft_lstadd_back(&this->first, ft_lstnew(ft_strdup(line)));
		if (len > gd->map_w)
			gd->map_w = len;
	}
	return (0);
}

int	line_check(t_data *gd, t_check *this, char *line)
{
	int	i;

	i = ft_spaceskip(line, 0);
	if (line[i] == '\0')
	{
		if (this->init_m == 1)
			return (save_map(gd, this, " "));
		return (0);
	}
	if (ft_strchr("012", line[i]))
		return (save_map(gd, this, line));
	if (this->init_m == 1)
		return (ft_error("Map reading"));
	else
	{
		if (line[i] == 'R')
			return (checkResolution(gd, this, line));
		else if (ft_strchr("NSEW", line[i]))
			return (checkTexture(gd, this, line));
		else if (line[i] == 'F' || line[i] == 'C')
			return (checkColor(gd, this, line));
		else
			return (ft_error("Line reading"));
	}
}

int	close_parse(t_data *gd, t_check *this, int ret)
{
	if (ret == -1)
		return (ft_error("Reading file error"));
	if (this->init_m == 0)
		return (ft_error("Unaviable map"));
	else
	{
		if (strlen(this->flag) == 8)
		{
			if (checkMap(gd, this) == -1)
			{
				ft_lstclear(&this->first, free);
				return (-1);
			}
			ft_lstclear(&this->first, free);
		}
		else
			return (ft_error("Not enough elements for map"));
	}
	if (strlen(this->flag) != 9)
	{
		secure_free(this->flag);
		return (ft_error("Missing elements"));
	}
	secure_free(this->flag);
	return (0);
}

int	ft_parse(t_data *gd, char *rut)
{
	t_check	this;
	int		ret;
	int		fd;
	char	*line;

	this.flag = ft_strdup("");
	this.init_m = 0;
	fd = open(rut, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret != -1)
	{
		if (line_check(gd, &this, line) == -1)
		{
			close(fd);
			secure_free(line);
			return (-1);
		}
		secure_free(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (close_parse(gd, &this, ret));
}
