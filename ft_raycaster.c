/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:57:48 by omercade          #+#    #+#             */
/*   Updated: 2021/03/18 20:48:54 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    raycast_step(t_raycast *raycast, t_data *gd)
{
    if (raycast->dirX < 0)
	{
		raycast->stepX = -1;
        raycast->sideDistX = (gd->actor.posX - raycast->mapX) * raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
       	raycast->sideDistX = (raycast->mapX + 1.0 - gd->actor.posX) * raycast->deltaDistX;
	}
	if (raycast->dirY < 0)
	{
		raycast->stepY = -1;
        raycast->sideDistY = (gd->actor.posY - raycast->mapY) * raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
        raycast->sideDistY = (raycast->mapY + 1.0 - gd->actor.posY) * raycast->deltaDistY;
	}
}

void    raycast_hit(t_raycast *raycast, t_data *gd)
{
    while (raycast->hit == 0)
	{
        if(raycast->sideDistX < raycast->sideDistY)
        {
        	raycast->sideDistX += raycast->deltaDistX;
          	raycast->mapX += raycast->stepX;
          	raycast->side = 0;
        }
        else
        {
          	raycast->sideDistY += raycast->deltaDistY;
          	raycast->mapY += raycast->stepY;
          	raycast->side = 1;
        }
        if(gd->game.map[raycast->mapX][raycast->mapY] > 0)
			raycast->hit = 1;
	}
    if (raycast->side == 0)
		raycast->perpWallDist = (raycast->mapX - gd->actor.posX + (1- raycast->stepX) / 2) / raycast->dirX;
	else
		raycast->perpWallDist = (raycast->mapY - gd->actor.posY + (1- raycast->stepY) / 2) / raycast->dirY;
}

void    raycast_draw(t_raycast *raycast, t_data *gd, t_render *render, int x)
{
    int pix = 0;
    while (pix < render->drawStart)
    {
        gd->game.img.data[pix * gd->game.scrW + x] = 0x02AFC4;
        pix++;
    }
    int *textn = gd->txtr.addr;
    while (render->drawStart < render->drawEnd)
	{
        int texY = (int)render->texPos & (gd->txtH - 1);
        render->texPos += render->step;
        int color = textn[gd->txtW * texY + render->texX];
        if(raycast->side == 1)
            color = (color >> 1) & 8355711;
		gd->game.img.data[render->drawStart * gd->game.scrW + x] = color;
		render->drawStart++;
	}
    while (render->drawEnd <= gd->game.scrH)
    {
        gd->game.img.data[render->drawEnd * gd->game.scrW + x] = 0x386E39;
        render->drawEnd++;
    }
}

void    raycast_wall(t_raycast *raycast, t_data *gd, int x)
{
    t_render    render;

    render.drawStart = -raycast->lineHeight / 2 + gd->game.scrH / 2;
	if (render.drawStart < 0)
		render.drawStart = 0;
	render.drawEnd = raycast->lineHeight / 2 + gd->game.scrH / 2;
	if (render.drawEnd >= gd->game.scrH)
		render.drawEnd = gd->game.scrH - 1;
    render.texNum = gd->game.map[raycast->mapX][raycast->mapY] - 1;
    if(raycast->side == 0)
        render.wallX = gd->actor.posX + raycast->perpWallDist * raycast->dirY;
    else
        render.wallX = gd->actor.posX + raycast->perpWallDist * raycast->dirX;
    render.wallX -= floor((render.wallX));
    render.step = 1.0 * gd->txtH / raycast->lineHeight;
    render.texPos = (render.drawStart - gd->game.scrH / 2 + raycast->lineHeight / 2) * render.step;
    raycast_draw(raycast, gd, &render, x);
}

void    ft_raycaster(t_data *gd, int x)
{
    t_raycast   raycast;
    double      cameraX;

    cameraX = 2 * x / (double) gd->game.scrW - 1;
    raycast.dirX = gd->actor.dirX + gd->actor.planeX * cameraX;
    raycast.dirY = gd->actor.dirY + gd->actor.planeY * cameraX;
    raycast.mapX = (int)gd->actor.posX;
    raycast.mapX = (int)gd->actor.posY;
    raycast.deltaDistX = fabs(1 / raycast.dirX);
    raycast.deltaDistY = fabs(1 / raycast.dirY);
    raycast_step(&raycast, gd);
    raycast_hit(&raycast, gd);
    raycast.lineHeight = (int)(gd->game.scrH / raycast.perpWallDist);
    raycast_wall(&raycast, gd, x);
}
