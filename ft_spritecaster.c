/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spritecaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 20:55:01 by omercade          #+#    #+#             */
/*   Updated: 2021/04/07 21:09:48 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void sortSprites(int *spriteOrder, double *spriteDist, int nSprites)
{
    int		i;
	int		j;
	int		a;
	double	b;

	i = 0;
	while (i < (nSprites - 1))
	{
		j = 0;
		while (j < (nSprites - 1 - i))
		{
			if (spriteDist[j] < spriteDist[j + 1])
			{
				b = spriteDist[j + 1];
				spriteDist[j + 1] = spriteDist[j];
				spriteDist[j] = b;
				a = spriteOrder[j + 1];
				spriteOrder[j + 1] = spriteOrder[j];
				spriteOrder[j] = a;
			}
			j++;
		}
		i++;
	}
}

void    sprite_draw(t_data *gd, t_spritecast *sprc, double *zBuffer)
{
    int         stripe;
    int         pix;
    t_sprites   sprTex;
    int         color;
    int         d;

    stripe = sprc->drawStartX;
    printf("BREAKPOINT---->stripe(%d), drawEnd(%d)\n", stripe, sprc->drawEndX);
    while (stripe < sprc->drawEndX)
    {
        sprTex.x = (int)(256 * (stripe - (-(sprc->spriteWidth) / 2 + sprc->spriteScreenX)) * gd->tex[4].width / sprc->spriteWidth) / 256;
        if(sprc->transformY > 0 && stripe > 0 && stripe < gd->cnv.w && sprc->transformY < zBuffer[stripe])
        {
            pix = sprc->drawStartY;
            while (pix < sprc->drawEndY)
            {
                d = (pix - sprc->vMoveScreen) * 256 - gd->cnv.h * 128 + sprc->spriteHeight * 128;
                sprTex.y = ((d * gd->tex[4].height) / sprc->spriteHeight) / 256;
                color = gd->tex[4].addr[gd->tex[4].width * sprTex.y + sprTex.x]; //?
                if((color & 0xFFFFFF) != 0)
                    gd->cnv.img.data[pix * gd->cnv.w + stripe] = color;
                pix++;
            }
        }
        stripe++;
    }
}

void    sprite_render(t_data *gd, int i, int *spriteOrder, double *zBuffer)
{
    t_spritecast    this;

    this.spriteX = gd->spr[spriteOrder[i]].x - gd->actor.posX;
    this.spriteY = gd->spr[spriteOrder[i]].y - gd->actor.posY;
    this.invDet = 1.0 / (gd->actor.planeX * gd->actor.dirY - gd->actor.dirX * gd->actor.planeY);
    this.transformX = this.invDet * (gd->actor.dirY * this.spriteX - gd->actor.dirX * this.spriteY);
    this.transformY = this.invDet * (-gd->actor.planeY * this.spriteX + gd->actor.planeX * this.spriteY);
    this.spriteScreenX = (int)(gd->cnv.w / 2) * (1 + this.transformX / this.transformY);
    this.vMoveScreen = (int) (0.0 / this.transformY);
    this.spriteHeight = abs((int)(gd->cnv.h / this.transformY)) / 1;
    this.drawStartY = -(this.spriteHeight) / 2 + gd->cnv.h / 2 + this.vMoveScreen;
    if (this.drawStartY < 0)
        this.drawStartY = 0;
    this.drawEndY = this.spriteHeight / 2 + gd->cnv.h / 2 + this.vMoveScreen;
    if (this.drawEndY >= gd->cnv.h)
        this.drawEndY = gd->cnv.h - 1;
    this.spriteWidth = abs((int)(gd->cnv.h / this.transformY)) / 1;
    this.drawStartX = -(this.spriteWidth) / 2 + this.spriteScreenX;
    if(this.drawStartX < 0)
        this.drawStartX = 0;
    this.drawEndX = this.spriteWidth / 2 + this.spriteScreenX;
    if(this.drawEndX >= gd->cnv.w)
        this.drawEndX = gd->cnv.w - 1;
    sprite_draw(gd, &this, zBuffer);
}

void    ft_spritecaster(t_data *gd, double *zBuffer)
{
    int     spriteOrder[gd->nSprites];
    double  spriteDist[gd->nSprites];
    int     i;

    i = 0;
    while (i < gd->nSprites)
    {
        spriteOrder[i] = i;
        spriteDist[i] = (pow((gd->actor.posX - gd->spr[i].x), 2) + pow((gd->actor.posY - gd->spr[i].y), 2));
        i++;
    }
    sortSprites(spriteOrder, spriteDist, gd->nSprites);
    i = 0;
    while (i < gd->nSprites)
    {
        sprite_render(gd, i, spriteOrder, zBuffer);
        i++;
    }
}
