/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:50:26 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 21:29:23 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

void	raycast_step(t_raycast *ryc, t_data *gd)
{
	if (ryc->dirX < 0)
	{
		ryc->stepX = -1;
		ryc->sideDistX = (gd->actor.posX - ryc->mapX) * ryc->deltaDistX;
	}
	else
	{
		ryc->stepX = 1;
		ryc->sideDistX = (ryc->mapX + 1.0 - gd->actor.posX) * ryc->deltaDistX;
	}
	if (ryc->dirY < 0)
	{
		ryc->stepY = -1;
		ryc->sideDistY = (gd->actor.posY - ryc->mapY) * ryc->deltaDistY;
	}
	else
	{
		ryc->stepY = 1;
		ryc->sideDistY = (ryc->mapY + 1.0 - gd->actor.posY) * ryc->deltaDistY;
	}
}

void	raycast_hit(t_raycast *ryc, t_data *gd)
{
	ryc->hit = 0;
	while (ryc->hit == 0)
	{
		if (ryc->sideDistX < ryc->sideDistY)
		{
			ryc->sideDistX += ryc->deltaDistX;
			ryc->mapX += ryc->stepX;
			ryc->side = 0;
		}
		else
		{
			ryc->sideDistY += ryc->deltaDistY;
			ryc->mapY += ryc->stepY;
			ryc->side = 1;
		}
		if (gd->map[ryc->mapX][ryc->mapY] == '1')
			ryc->hit = 1;
	}
}

void	raycast_draw(t_raycast *ryc, t_data *gd, t_render *render, int x)
{
	t_sprites	p;
	int			color;
	int			texY;

	p.x = x;
	p.y = 0;
	color_fill(gd, render->drawStart, p, gd->color[0]);		//sustituir por skybox
	p.y = render->drawStart;
	while (p.y < render->drawEnd)
	{
		texY = (int)render->texPos & (gd->tex[ryc->face].height - 1);
		render->texPos += render->step;
		color = gd->tex[ryc->face].addr[gd->tex[ryc->face].height
			* texY + render->texX];
		gd->cnv.img.data[p.y * gd->cnv.w + x] = color;
		p.y++;
	}
	p.y = render->drawEnd;
	color_fill(gd, gd->cnv.h, p, gd->color[1]);				//sustituir por ground_texture
}

void	raycast_wall(t_raycast *ryc, t_data *gd, int x)
{
	t_render	this;

	ryc->lineHeight = (int)(gd->cnv.h / ryc->perpWallDist);
	this.drawStart = -(ryc->lineHeight) / 2 + gd->cnv.h / 2 + gd->actor.posZ;
	if (this.drawStart < 0)
		this.drawStart = 0;
	this.drawEnd = ryc->lineHeight / 2 + gd->cnv.h / 2 + gd->actor.posZ;
	if (this.drawEnd >= gd->cnv.h)
		this.drawEnd = gd->cnv.h - 1;
	if (ryc->side == 0)
		this.wallX = gd->actor.posY + ryc->perpWallDist * ryc->dirY;
	else
		this.wallX = gd->actor.posX + ryc->perpWallDist * ryc->dirX;
	this.wallX -= floor((this.wallX));
	this.texX = (int)(this.wallX * (double)gd->tex[ryc->face].width);
	if (ryc->side == 0 && ryc->dirX > 0)
		this.texX = gd->tex[ryc->face].width - this.texX - 1;
	if (ryc->side == 1 && ryc->dirY < 0)
		this.texX = gd->tex[ryc->face].width - this.texX - 1;
	this.step = 1.0 * gd->tex[ryc->face].height / ryc->lineHeight;
	this.texPos = (this.drawStart - gd->cnv.h / 2
			+ ryc->lineHeight / 2) * this.step;
	raycast_draw(ryc, gd, &this, x);
}

double	ft_raycast(t_data *gd, int x)
{
	t_raycast	this;
	double		cameraX;

	cameraX = 2 * x / (double) gd->cnv.w - 1;
	this.dirX = gd->actor.dirX + gd->actor.planeX * cameraX;
	this.dirY = gd->actor.dirY + gd->actor.planeY * cameraX;
	this.mapX = (int)gd->actor.posX;
	this.mapY = (int)gd->actor.posY;
	this.deltaDistX = fabs(1 / this.dirX);
	this.deltaDistY = fabs(1 / this.dirY);
	raycast_step(&this, gd);
	raycast_hit(&this, gd);
	if (this.side == 0)
		this.perpWallDist = (this.mapX - gd->actor.posX
				+ (1 - this.stepX) / 2) / this.dirX;
	else
		this.perpWallDist = (this.mapY - gd->actor.posY
				+ (1 - this.stepY) / 2) / this.dirY;
	raycast_wall(&this, gd, x);
	return (this.perpWallDist);
}

