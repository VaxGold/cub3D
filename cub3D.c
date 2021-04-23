/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:06 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:30:08 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	awake(t_data *gd, char *arg)
{
	if (ft_extension(arg, ".cub") == -1)
		return (-1);
	gd->mlx = mlx_init();
	gd->nSprites = 0;
	if (ft_parse(gd, arg) == -1)
		return (-1);
	gd->cnv.win = mlx_new_window(gd->mlx, gd->cnv.w, gd->cnv.h, "cub3D");
	gd->cnv.img.ptr = mlx_new_image(gd->mlx, gd->cnv.w, gd->cnv.h);
	gd->cnv.img.data = (int *)mlx_get_data_addr(gd->cnv.img.ptr,
			&gd->cnv.img.bpp, &gd->cnv.img.size_l, &gd->cnv.img.endian);
	gd->actor.mvSpd = 0.1;
	gd->actor.rotSpd = 0.075;
	countSprites (gd);
	return (0);
}

int	update(t_data *gd)
{
	int		x;
	double	*zBuffer;

	ft_transform(gd);
	zBuffer = malloc(sizeof(double) * gd->cnv.w);
	if (!zBuffer)
		exit(0);
	x = 0;
	while (x < gd->cnv.w)
	{
		zBuffer[x] = ft_raycast(gd, x);
		x++;
	}
	ft_sprites(gd, zBuffer);
	secure_free(zBuffer);
	mlx_put_image_to_window(gd->mlx, gd->cnv.win, gd->cnv.img.ptr, 0, 0);
	return (0);
}

int	screen_capture(t_data *gd)
{
	int		x;
	double	*zBuffer;

	zBuffer = malloc(sizeof(double) * gd->cnv.w);
	if (!zBuffer)
		exit(0);
	x = 0;
	while (x < gd->cnv.w)
	{
		zBuffer[x] = ft_raycast(gd, x);
		x++;
	}
	ft_sprites(gd, zBuffer);
	secure_free(zBuffer);
	ft_save_img(gd, gd->cnv.img.data);
	exit(0);
}

int	main(int nargs, char **xargs)
{
	t_data	this;

	if (!(nargs == 2 || nargs == 3))
		return (ft_error("Invalid arguments"));
	if (awake(&this, xargs[1]) != -1)
	{
		if (nargs == 3 && ft_strlen(xargs[2]) == 6
			&& ft_strncmp(xargs[2], "--save", ft_strlen(xargs[2])) == 0)
			screen_capture(&this);
		else if (nargs == 2)
		{
			mlx_hook(this.cnv.win, X_EVENT_KEY_PRESS, 0, &key_press, &this);
			mlx_hook(this.cnv.win, X_EVENT_KEY_RELEASE, 0, &key_release, &this);
			mlx_hook(this.cnv.win, X_EVENT_KEY_EXIT, 0, &close_window, &this);
			mlx_loop_hook(this.mlx, &update, &this);
			mlx_loop(this.mlx);
		}
		else
			ft_error("Invalid arguments");
	}
	return (0);
}
