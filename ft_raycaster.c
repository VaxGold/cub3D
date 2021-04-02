/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:57:48 by omercade          #+#    #+#             */
/*   Updated: 2021/04/02 21:11:21 by omercade         ###   ########.fr       */
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
        if(gd->map[raycast->mapX][raycast->mapY] == 1)
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
    int color;
    while (pix < render->drawStart)
    {
        gd->cnv.img.data[pix * gd->cnv.w + x] = gd->color[0];
        pix++;
    }
    while (render->drawStart < render->drawEnd)
	{
        int texY = (int)render->texPos & (TEX_H - 1);
        render->texPos += render->step;
        color = gd->tex[raycast->side].addr[TEX_W * texY + render->texX];
		gd->cnv.img.data[render->drawStart * gd->cnv.w + x] = color;
		render->drawStart++;
	}
    while (render->drawEnd <= gd->cnv.h)
    {
        gd->cnv.img.data[render->drawEnd * gd->cnv.h + x] = gd->color[1];
        render->drawEnd++;
    }
}

void    raycast_wall(t_raycast *raycast, t_data *gd, int x)
{
    t_render    render;

    render.drawStart = -raycast->lineHeight / 2 + gd->cnv.h / 2;
	if (render.drawStart < 0)
		render.drawStart = 0;
	render.drawEnd = raycast->lineHeight / 2 + gd->cnv.h / 2;
	if (render.drawEnd >= gd->cnv.h)
		render.drawEnd = gd->cnv.h - 1;
    printf("------->|{%d}[%d]{%c}|<-------\n", raycast->mapX, raycast->mapY, gd->map[raycast->mapX][raycast->mapY]);
    render.texNum = (gd->map[raycast->mapX][raycast->mapY] - 48) - 1;
    printf("TEST2...\n");
    if(raycast->side == 0)
        render.wallX = gd->actor.posX + raycast->perpWallDist * raycast->dirY;
    else
        render.wallX = gd->actor.posX + raycast->perpWallDist * raycast->dirX;
    printf("TEST4...\n");
    render.wallX -= floor((render.wallX));
    render.step = 1.0 * TEX_H / raycast->lineHeight;
    render.texPos = (render.drawStart - gd->cnv.h / 2 + raycast->lineHeight / 2) * render.step;
    raycast_draw(raycast, gd, &render, x);
}

double    ft_raycaster(t_data *gd, int x)
{
    t_raycast   raycast;
    double      cameraX;

    cameraX = 2 * x / (double) gd->cnv.w - 1;
    raycast.dirX = gd->actor.dirX + gd->actor.planeX * cameraX;
    raycast.dirY = gd->actor.dirY + gd->actor.planeY * cameraX;
    raycast.mapX = (int)gd->actor.posX;
    raycast.mapX = (int)gd->actor.posY;
    raycast.deltaDistX = fabs(1 / raycast.dirX);
    raycast.deltaDistY = fabs(1 / raycast.dirY);
    raycast_step(&raycast, gd);
    raycast_hit(&raycast, gd);
    raycast.lineHeight = (int)(gd->cnv.h / raycast.perpWallDist);
    raycast_wall(&raycast, gd, x);
    return(raycast.perpWallDist);
}
