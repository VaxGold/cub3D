/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:01:17 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:07:42 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	flood_fill(t_data *gd, char **map, int posX, int posY)
{
	char	c;
	int		n;

	if (posX < 0 || posX >= gd->map_h || posY < 0 || posY >= gd->map_w)
		return (ft_error("Flood fill"));
	c = map[posX][posY];
	if (c == '3' || c == '1')
		return (0);
	map[posX][posY] = '3';
	n = flood_fill(gd, map, posX, posY - 1);
	if (n == 0)
		n = flood_fill(gd, map, posX, posY + 1);
	if (n == 0)
		n = flood_fill(gd, map, posX - 1, posY);
	if (n == 0)
		n = flood_fill(gd, map, posX + 1, posY);
	return (n);
}

void	init_map(t_data *gd, t_check *this)
{
	gd->actor.dirX = -1;
	gd->actor.dirY = 0;
	gd->actor.planeX = 0;
	gd->actor.planeY = 0.66;
	gd->map_h = ft_lstsize(this->first);
	gd->map = malloc(sizeof(char *) * gd->map_h + 1);
	if (!gd->map)
		exit(0);
}

int	lst2map(t_data *gd, t_list *first)
{
	int		i;
	t_list	*map_line;

	map_line = first;
	i = 0;
	while (map_line != NULL)
	{
		gd->map[i] = malloc(sizeof(char) * gd->map_w + 1);
		if (!gd->map[i])
			exit(0);
		if (fill_map(gd, map_line->content, i) == -1)
			return (-1);
		map_line = map_line->next;
		i++;
	}
	gd->map[i] = "\0";
	return (0);
}

int	checkMap(t_data *gd, t_check *this)
{
	char	**aux;

	init_map(gd, this);
	if (lst2map(gd, this->first) == -1)
		return (-1);
	if (!gd->actor.posX && !gd->actor.posY)
		return (ft_error("No player"));
	aux = ft_matrixcpy(gd->map_h, gd->map);
	if (!aux)
		return (ft_error("Memory alloc"));
	if (flood_fill(gd, aux, gd->actor.posX, gd->actor.posY) == -1)
	{
		free_2Dchar(aux);
		return (-1);
	}
	free_2Dchar(aux);
	return (ft_flgcmp(this, 'M'));
}
