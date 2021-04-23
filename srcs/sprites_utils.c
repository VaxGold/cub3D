/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:11:22 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:07:05 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	sortSprites(int *spriteOrder, double *spriteDist, int nSprites)
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

void	countSprites(t_data *gd)
{
	int	i;
	int	j;
	int	n;

	gd->spr = malloc(sizeof(t_sprites) * gd->nSprites);
	if (!gd->spr)
		exit(0);
	n = 0;
	i = 0;
	while (i < gd->map_h)
	{
		j = 0;
		while (j < gd->map_w)
		{
			if (gd->map[i][j] == '2')
			{
				gd->spr[n].x = i;
				gd->spr[n].y = j;
				n++;
			}
			j++;
		}
		i++;
	}
}

void	desallocSprites(double *spriteDist, int *spriteOrder, double *zBuffer)
{
	if (!spriteOrder || !spriteDist)
	{
		secure_free(spriteOrder);
		secure_free(spriteDist);
		secure_free(zBuffer);
		exit(0);
	}
}
