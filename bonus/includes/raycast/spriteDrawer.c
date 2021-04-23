/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteDrawer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:15:43 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 21:29:20 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

void	color_info(t_data *gd, t_spritecast *sprc, t_sprites sprTex, int stripe)
{
	int			pix;
	int			color;
	int			d;

	pix = sprc->drawStartY;
	while (pix < sprc->drawEndY)
	{
		d = (pix - sprc->vMoveScreen) * 256
			- gd->cnv.h * 128 + sprc->spriteHeight * 128;
		sprTex.y = ((d * gd->tex[4].height) / sprc->spriteHeight) / 256;
		color = gd->tex[4].addr[gd->tex[4].width * sprTex.y + sprTex.x];
		if ((color & 0xFFFFFF) != 0)
			gd->cnv.img.data[pix * gd->cnv.w + stripe] = color;
		pix++;
	}
}

void	sprite_draw(t_data *gd, t_spritecast *sprc, double *zBuffer)
{
	int			stripe;
	t_sprites	sprTex;

	stripe = sprc->drawStartX;
	while (stripe < sprc->drawEndX)
	{
		sprTex.x = (int)(256 * (stripe
					- (-(sprc->spriteWidth) / 2 + sprc->spriteScreenX))
				* gd->tex[4].width / sprc->spriteWidth) / 256;
		sprTex.y = 0;
		if (sprc->transformY > 0 && stripe > 0
			&& stripe < gd->cnv.w && sprc->transformY < zBuffer[stripe])
			color_info(gd, sprc, sprTex, stripe);
		stripe++;
	}
}

void	render_info(t_data *gd, t_spritecast *sprc, int i, int *spriteOrder)
{
	sprc->spriteX = gd->spr[spriteOrder[i]].x + 0.5 - gd->actor.posX;
	sprc->spriteY = gd->spr[spriteOrder[i]].y + 0.5 - gd->actor.posY;
	sprc->invDet = 1.0 / (gd->actor.planeX
			* gd->actor.dirY - gd->actor.dirX * gd->actor.planeY);
	sprc->transformX = sprc->invDet * (gd->actor.dirY
			* sprc->spriteX - gd->actor.dirX * sprc->spriteY);
	sprc->transformY = sprc->invDet * (-gd->actor.planeY
			* sprc->spriteX + gd->actor.planeX * sprc->spriteY);
	sprc->spriteScreenX = (int)(gd->cnv.w / 2)
		*(1 + sprc->transformX / sprc->transformY);
	sprc->vMoveScreen = (int)(10 / sprc->transformY);
	sprc->spriteHeight = abs((int)(gd->cnv.h / sprc->transformY)) / 1;
}

void	sprite_render(t_data *gd, int i, int *spriteOrder, double *zBuffer)
{
	t_spritecast	this;

	render_info(gd, &this, i, spriteOrder);
	this.drawStartY = -(this.spriteHeight)
		/ 2 + gd->cnv.h / 2 + this.vMoveScreen;
	if (this.drawStartY < 0)
		this.drawStartY = 0;
	this.drawEndY = this.spriteHeight / 2 + gd->cnv.h / 2 + this.vMoveScreen;
	if (this.drawEndY >= gd->cnv.h)
		this.drawEndY = gd->cnv.h - 1;
	this.spriteWidth = abs((int)(gd->cnv.h / this.transformY)) / 1;
	this.drawStartX = -(this.spriteWidth) / 2 + this.spriteScreenX;
	if (this.drawStartX < 0)
		this.drawStartX = 0;
	this.drawEndX = this.spriteWidth / 2 + this.spriteScreenX;
	if (this.drawEndX >= gd->cnv.w)
		this.drawEndX = gd->cnv.w - 1;
	sprite_draw(gd, &this, zBuffer);
}

void	ft_sprites(t_data *gd, double *zBuffer)
{
	int		*spriteOrder;
	double	*spriteDist;
	int		i;

	spriteOrder = malloc(gd->nSprites * sizeof(int));
	spriteDist = malloc(gd->nSprites * sizeof(double));
	desallocSprites(spriteDist, spriteOrder, zBuffer);
	i = 0;
	while (i < gd->nSprites)
	{
		spriteOrder[i] = i;
		spriteDist[i] = (pow((gd->actor.posX - gd->spr[i].x), 2)
				+ pow((gd->actor.posY - gd->spr[i].y), 2));
		i++;
	}
	sortSprites(spriteOrder, spriteDist, gd->nSprites);
	i = 0;
	while (i < gd->nSprites)
	{
		sprite_render(gd, i, spriteOrder, zBuffer);
		i++;
	}
	secure_free(spriteOrder);
	secure_free(spriteDist);
}
