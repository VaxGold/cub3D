/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:06 by omercade          #+#    #+#             */
/*   Updated: 2021/04/07 21:03:29 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//------------------------------------ AWAKE ------------------------------------//
void	sprite_recorder(t_data *gd)
{
	int i;
	int j;
	int	n;

	gd->spr = malloc(sizeof(t_sprites) * gd->nSprites);
	n  = 0;
	i = 0;
	while(i < gd->map_w)
	{
		j = 0;
		while (j < gd->map_h)
		{
			if (gd->map[i / gd->map_w][i % gd->map_w] == '2')
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

int		awake(t_data *gd, char *arg)
{
	gd->mlx = mlx_init();
	gd->nSprites = 0;
	if(ft_reader(gd, arg) == -1)
		return(-1);
	gd->cnv.win = mlx_new_window(gd->mlx, gd->cnv.w, gd->cnv.h, "cub3D");
	gd->cnv.img.ptr = mlx_new_image(gd->mlx, gd->cnv.w, gd->cnv.h);
	gd->cnv.img.data = (int *)mlx_get_data_addr(gd->cnv.img.ptr, &gd->cnv.img.bpp, &gd->cnv.img.size_l, &gd->cnv.img.endian);
	gd->actor.mvSpd = 0.1;
	gd->actor.rotSpd = 0.075;
	sprite_recorder(gd);
	return(0);
}

//------------------------------------ UPDATE ------------------------------------//
int     update(t_data *gd)
{
	int     x;
	double  zBuffer[gd->cnv.w];

	ft_transform(gd);
	x = 0;
	while (x < gd->cnv.w)
	{
		zBuffer[x] = ft_raycaster(gd, x);
		x++;
	}
	ft_spritecaster(gd, zBuffer);
	mlx_put_image_to_window(gd->mlx, gd->cnv.win, gd->cnv.img.ptr, 0, 0);
	return(0);
}

//------------------------------------ START ------------------------------------//
int     main(int nargs, char **xargs)
{
	t_data this;

	if (nargs == 2 || nargs == 3)
	{
		if (awake(&this, xargs[1]) == -1)
			exit(0);
		if (nargs == 2)
		{
			mlx_hook(this.cnv.win, X_EVENT_KEY_PRESS, 0, &key_press, &this);
			mlx_hook(this.cnv.win, X_EVENT_KEY_RELEASE, 0, &key_release, &this);
			mlx_hook(this.cnv.win, X_EVENT_KEY_EXIT, 0, &close_window, &this);
			mlx_loop_hook(this.mlx, &update, &this);
			mlx_loop(this.mlx);
		}
		else if (nargs == 3 && ft_strncmp(xargs[2], "--save", ft_strlen(xargs[2])) == 0)
		{
			printf("SCREEN SHOOT!");
			close_window(&this);
		}
	}
	return(0);
}