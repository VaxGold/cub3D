/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:00 by omercade          #+#    #+#             */
/*   Updated: 2021/04/02 20:21:51 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    player_generator(t_data *gd, int posX, int posY, char dir)
{
	double  rot;
	double oldDirX;

	rot = 0;
	gd->actor.posX = (double)posX;
	gd->actor.posY = (double)posY;
	gd->map[posX][posY] = '0';
	if (dir == 'S')
		rot = 180;
	else if (dir == 'E')
		rot = 90;
	else if (dir == 'W')
		rot = 270;
	oldDirX = gd->actor.dirX;
	gd->actor.dirX = gd->actor.dirX * cos(rot * M_PI / 180) - gd->actor.dirY * sin(rot * M_PI / 180);
	gd->actor.dirY = oldDirX * sin(rot * M_PI / 180) + gd->actor.dirY * cos(rot * M_PI / 180);
	oldDirX = gd->actor.planeX;
	gd->actor.planeX = gd->actor.planeX * cos(rot * M_PI / 180) - gd->actor.planeY * sin(rot * M_PI / 180);
	gd->actor.planeY = oldDirX * sin(rot * M_PI / 180) + gd->actor.planeY * cos(rot * M_PI / 180);
}

int     fill_map(t_data *gd, char *str, int n)
{
	int     i;

	i = 0;
	while (i < gd->map_w && str[i] != 0)
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == '2')
			gd->map[n][i] = str[i];
		else if (str[i] == ' ')
			gd->map[n][i] = '0';
		else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			if (!gd->actor.posX && !gd->actor.posY)
				player_generator(gd, n, i, str[i]);
			else
				return(error_display("MULTIPLE PLAYER"));
		}
		else
			return(error_display("INVALID MAP CHARACTER"));
		i++;
	}
	if (i < gd->map_w && str[i] == 0)
		while(i < gd->map_w)
			gd->map[n][i++] = '0';
	gd->map[n][i] = '\0';
	return(0);
}

int     flood_fill(t_data *gd, char **map, int posX, int posY)
{
	char	c;
	int		n;

	if (posX < 0 || posX >= gd->map_h || posY < 0 || posY >= gd->map_w)
		return(error_display("FLOOD FILL"));
	c = map[posX][posY];
	if (c == '3' || c == '1')
		return(0);
	map[posX][posY] = '3';
	n = flood_fill(gd, map, posX, posY - 1);
	if (n == 0)
		n = flood_fill(gd, map, posX, posY + 1);
	if (n == 0)
		n = flood_fill(gd, map, posX - 1, posY);
	if (n == 0)
		n = flood_fill(gd, map, posX + 1, posY);
	return(n);
}

char	**matrix_cpy(int rows, char **map)
{
	char	**matrix;
	int		i;
	
	i = 0;
	matrix = (char**)malloc((rows + 1) * sizeof(char*));
	while (i < rows)
	{
		matrix[i] = ft_strdup(map[i]);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);

}

int     ft_check_map(t_data *gd, t_check *this)
{
	int     i;
	char	**aux;
	t_list  *map_line;

	gd->actor.dirX = -1;
	gd->actor.dirY = 0;
	gd->actor.planeX = 0;
	gd->actor.planeY = 0.66;
	map_line = this->first;
	gd->map_h = ft_lstsize(this->first);
	gd->map = malloc(sizeof(char *) * gd->map_h + 1);
	i = 0;
	while (map_line != NULL)
	{
		gd->map[i] = malloc(sizeof(char) * gd->map_w + 1);
		if (fill_map(gd, map_line->content, i) == -1)
			return(-1);
		map_line = map_line->next;
		i++;
	}
	gd->map[i] = "\0";
	aux = matrix_cpy(gd->map_h, gd->map);
	if (flood_fill(gd, aux, gd->actor.posX, gd->actor.posY) == -1)
		return(error_display("MAP"));
	return(check_flag(this, 'M'));
}