/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:06 by omercade          #+#    #+#             */
/*   Updated: 2021/04/02 20:56:11 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//------------------------------------ ERROR ------------------------------------//
int		ft_error(char *str)
{
	printf("%s ERROR...\n", str);
	return(1);
}

//------------------------------------ AWAKE ------------------------------------//
void	awake(t_data *gd)
{
	gd->mlx = mlx_init();
	gd->cnv.win = mlx_new_window(gd->mlx, gd->cnv.w, gd->cnv.h, "cub3D");
	gd->cnv.img.ptr = mlx_new_image(gd->mlx, gd->cnv.w, gd->cnv.h);
	gd->cnv.img.data = (int *)mlx_get_data_addr(gd->cnv.img.ptr, &gd->cnv.img.bpp, &gd->cnv.img.size_l, &gd->cnv.img.endian);
}

//------------------------------------ EXIT ------------------------------------//
int     close_game(t_data *gd)
{
	mlx_destroy_window(gd->mlx, gd->cnv.win);
	exit(0);
}

//------------------------------------ UPDATE ------------------------------------//
int     update(t_data *gd)
{
	int     x;
	double  zBuffer[gd->cnv.w];

	ft_transform(gd);
	x = -1;
	while (++x < gd->cnv.w)
		zBuffer[x] = ft_raycaster(gd, x);
	printf("SPRITES...\n");
	//ft_spritecaster();
	mlx_put_image_to_window(gd->mlx, gd->cnv.win, gd->cnv.img.ptr, 0, 0);
	return(0);
}

//------------------------------------ START ------------------------------------//
int     main(int nargs, char **xargs)
{
	t_data this;

	if (nargs == 2 || nargs == 3)
	{
		printf("STARTING...\n");
		awake(&this);
		printf("AWAKED!\n");
		if(ft_reader(&this, xargs[1]))
		{
			printf("Reading error...\n");
			exit(0);
		}
		printf("FILE CHECKED!\n");
		if (nargs == 2)
		{
			printf("GAME...\n");
			key_events(&this);
			mlx_loop_hook(this.mlx, &update, &this);
			mlx_loop(this.mlx);
		}
		else if (nargs == 3 && ft_strncmp(xargs[2], "--save", ft_strlen(xargs[2])) == 0)
		{
			printf("SCREEN SHOOT!");
			close_game(&this);
		}
		printf("EXIT!");
	}
	return(0);
}