/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:08:05 by omercade          #+#    #+#             */
/*   Updated: 2021/04/19 20:50:50 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	yaw(t_data *gd, double spd)
{
	double	oldDirX;

	oldDirX = gd->actor.dirX;
	gd->actor.dirX = gd->actor.dirX * cos(gd->axis.rot * spd)
		- gd->actor.dirY * sin(gd->axis.rot * spd);
	gd->actor.dirY = oldDirX * sin(gd->axis.rot * spd)
		+ gd->actor.dirY * cos(gd->axis.rot * spd);
	oldDirX = gd->actor.planeX;
	gd->actor.planeX = gd->actor.planeX * cos(gd->axis.rot * spd)
		- gd->actor.planeY * sin(gd->axis.rot * spd);
	gd->actor.planeY = oldDirX * sin(gd->axis.rot * spd)
		+ gd->actor.planeY * cos(gd->axis.rot * spd);
}

void	displacement(t_data *gd, double spd)
{
	double	normalX;
	double	normalY;

	normalX = gd->actor.dirX * cos(90 * M_PI / 180)
		- gd->actor.dirY * sin(90 * M_PI / 180);
	normalY = gd->actor.dirX * sin(90 * M_PI / 180)
		+ gd->actor.dirY * cos(90 * M_PI / 180);
	if (gd->map[(int)(gd->actor.posX + gd->axis.x * gd->actor.dirX
			* (spd + 0.1))][(int)gd->actor.posY] == '0')
		gd->actor.posX = gd->actor.posX + gd->axis.x * (gd->actor.dirX * spd);
	if (gd->map[(int)gd->actor.posX][(int)(gd->actor.posY
		+ gd->axis.x * gd->actor.dirY * (spd + 0.1))] == '0')
		gd->actor.posY = gd->actor.posY + gd->axis.x * (gd->actor.dirY * spd);
	if (gd->map[(int)(gd->actor.posX + gd->axis.y * normalX
			* (spd + 0.1))][(int)gd->actor.posY] == '0')
		gd->actor.posX = gd->actor.posX + gd->axis.y * (normalX * spd);
	if (gd->map[(int)gd->actor.posX][(int)(gd->actor.posY
		+ gd->axis.y * normalY * (spd + 0.1))] == '0')
		gd->actor.posY = gd->actor.posY + gd->axis.y * (normalY * spd);
}

void	ft_transform(t_data *gd)
{
	double	spd;

	spd = gd->actor.rotSpd;
	yaw(gd, spd);
	if (gd->axis.x != 0 && gd->axis.y != 0)
		spd = gd->actor.mvSpd * (sqrt(2) / 2);
	else
		spd = gd->actor.mvSpd;
	displacement(gd, spd);
}
