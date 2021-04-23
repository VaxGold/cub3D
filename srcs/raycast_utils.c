/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:11:39 by omercade          #+#    #+#             */
/*   Updated: 2021/04/14 18:23:15 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	face_orientation(t_data *gd, t_raycast *ryc, int side)
{
	ryc->side = side;
	if (gd->actor.posX > (double)ryc->mapX)
	{
		if (ryc->side == 1 && gd->actor.posY > ryc->mapY)
			ryc->face = 2;
		else if (ryc->side == 1 && gd->actor.posY < ryc->mapY)
			ryc->face = 1;
		else
			ryc->face = 3;
	}
	else
	{
		if (ryc->side == 1 && gd->actor.posY > ryc->mapY)
			ryc->face = 2;
		else if (ryc->side == 1 && gd->actor.posY < ryc->mapY)
			ryc->face = 1;
		else
			ryc->face = 0;
	}
}

void	color_fill(t_data *gd, int end, t_sprites point, int color)
{
	while (point.y < end)
	{
		gd->cnv.img.data[point.y * gd->cnv.w + point.x] = color;
		point.y++;
	}
}
