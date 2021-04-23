/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:33:30 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 19:50:06 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	game(t_data *gd)
{
	int		x;
	double	*zBuffer;

	transform(gd);
	zBuffer = malloc(sizeof(double) * gd->cnv.w);
	if (!zBuffer)
		exit(0);
	x = 0;
	while (x < gd->cnv.w)
	{
		zBuffer[x] = raycaster(gd, x);
		x++;
	}
	spriteDrawer(gd, zBuffer);
	secure_free(zBuffer);
	mlx_put_image_to_window(gd->mlx, gd->cnv.win, gd->cnv.img.ptr, 0, 0);
	return (0);
}
