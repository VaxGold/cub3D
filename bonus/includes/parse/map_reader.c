/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:49:14 by omercade          #+#    #+#             */
/*   Updated: 2021/04/21 18:54:35 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

int	lst_map(t_data *gd, char *line, t_list *first)
{
	int	len;

	len = ft_strlen(line);
	if (!first)
	{
		first = ft_lstnew(ft_strdup(line));
		gd->map.w = len;
	}
	else
	{
		ft_lstadd_back(&first, ft_lstnew(ft_strdup(line)));
		if (len > gd->map.w)
			gd->map.w = len;
	}
	return (0);
}

int		line_check(t_data *gd, char *line, t_list *first)
{
	int		i;
	
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'W')
		gd->map.wTex = texture_save(gd, line);
	else if (line[i] == 'F')
		gd->map.fTex = texture_save(gd, line);
	else if (line[i] == 'C')
		gd->map.sBox = skybox_save(gd, line);
	else if (line[i] == 'S')
		return(sprites_save(gd, line));
	else if (line[i] == 'O')
		return(objs_save(gd, line));
	else if (line[i] >= '0' && line[i] >= '9')
		return(temp_map(gd, line, first));
	else if (line[i] != '\0')
		return(-1);
	return (0);
}

int		line_check(t_data *gd, char *line, t_list *first)
{
	int		i;
	char	**data;
	
	if (ft_strchr("WFCSO", line[i]))
	{
		data = ft_split((const char)line, ' ');
	}
	else
	{
		if (line[i] != '\n' && line[i] != '\0')
			lst_map(gd, line, first);
	}
	return (0);
}

int		map_reader(t_data *gd)
{
	int		fd;
	int		ret;
	char	*line;
	t_list	*first;
	
	fd = open(gd->map_selector[gd->world], O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret != -1)
	{
		if (line_check(gd, line, first) == -1)
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
	if (ret != -1)
		save_map(gd, first);
	else
		return (-1);
	return (0);
}