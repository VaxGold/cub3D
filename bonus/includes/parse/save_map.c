/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:29:09 by omercade          #+#    #+#             */
/*   Updated: 2021/04/21 18:54:36 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

int	flood_fill(t_data *gd, char **map, int posX, int posY)
{
	char	c;
	int		n;

	if (posX < 0 || posX >= gd->map.h || posY < 0 || posY >= gd->map.w)
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

void	init_map(t_data *gd, t_list *first)
{
	gd->ply.dirX = -1;
	gd->ply.dirY = 0;
	gd->ply.planeX = 0;
	gd->ply.planeY = 0.66;
	gd->map.h = ft_lstsize(first);
	gd->map.this = malloc(sizeof(char *) * gd->map.h + 1);
	if (!gd->map.this)
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
		gd->map.this[i] = malloc(sizeof(char) * gd->map.w + 1);
		if (!gd->map.this[i])
			exit(0);
		if (fill_map(gd, map_line->content, i) == -1)
			return (-1);
		map_line = map_line->next;
		i++;
	}
	gd->map.this[i] = "\0";
	return (0);
}

int	save_map(t_data *gd, t_list *first)
{
	char	**aux;

	init_map(gd, first);
	if (lst2map(gd, first) == -1)
		return (-1);
	if (!gd->ply.posX && !gd->ply.posY)
		return (ft_error("No player"));
	aux = ft_matrixcpy(gd->map.h, gd->map.this);
	if (!aux)
		return (ft_error("Memory alloc"));
	if (flood_fill(gd, aux, gd->ply.posX, gd->ply.posY) == -1)
	{
		free_2Dchar(aux);
		return (-1);
	}
	free_2Dchar(aux);
	return (0);
}
