/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:09:49 by omercade          #+#    #+#             */
/*   Updated: 2021/04/13 21:25:11 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	player_generator(t_data *gd, int posX, int posY, char dir)
{
	double	rot;
	double	oldDirX;

	rot = 0;
	gd->actor.posX = (double)posX + 0.5;
	gd->actor.posY = (double)posY + 0.5;
	gd->map[posX][posY] = '0';
	if (dir == 'S')
		rot = 180;
	else if (dir == 'E')
		rot = 270;
	else if (dir == 'W')
		rot = 90;
	oldDirX = gd->actor.dirX;
	gd->actor.dirX = gd->actor.dirX * cos(rot * M_PI / 180)
		- gd->actor.dirY * sin(rot * M_PI / 180);
	gd->actor.dirY = oldDirX * sin(rot * M_PI / 180)
		+ gd->actor.dirY * cos(rot * M_PI / 180);
	oldDirX = gd->actor.planeX;
	gd->actor.planeX = gd->actor.planeX * cos(rot * M_PI / 180)
		- gd->actor.planeY * sin(rot * M_PI / 180);
	gd->actor.planeY = oldDirX * sin(rot * M_PI / 180)
		+ gd->actor.planeY * cos(rot * M_PI / 180);
}

int	map_writer(t_data *gd, char *str, int i, int n)
{
	if (str[i] == '0' || str[i] == '1' || str[i] == '2')
	{
		gd->map[n][i] = str[i];
		if (str[i] == '2')
			gd->nSprites++;
	}
	else if (str[i] == ' ')
		gd->map[n][i] = '0';
	else if (ft_strchr("NSEW", str[i]))
	{
		if (!gd->actor.posX && !gd->actor.posY)
			player_generator(gd, n, i, str[i]);
		else
			return (ft_error("Multiple players"));
	}
	else
		return (ft_error("Invalid map"));
	return (0);
}

int	map_close(t_data *gd, char *str, int i, int n)
{
	if (i < gd->map_w && str[i] == 0)
		while (i < gd->map_w)
			gd->map[n][i++] = '0';
	gd->map[n][i] = '\0';
	return (0);
}

int	fill_map(t_data *gd, char *str, int n)
{
	int	i;

	i = 0;
	while (i < gd->map_w && str[i] != 0)
	{
		if (map_writer(gd, str, i, n) == -1)
			return (-1);
		i++;
	}
	return (map_close(gd, str, i, n));
}
