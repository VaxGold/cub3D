/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:39:08 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 21:31:43 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	awake(t_data *gd)
{
	gd->state = 0;
	gd->mlx = mlx_init();
	gd->cnv.win = mlx_new_window(gd->mlx, gd->cnv.w, gd->cnv.h, "cub3D");
	gd->cnv.img.ptr = mlx_new_image(gd->mlx, gd->cnv.w, gd->cnv.h);
	gd->cnv.img.data = (int *)mlx_get_data_addr(gd->cnv.img.ptr,
			&gd->cnv.img.bpp, &gd->cnv.img.size_l, &gd->cnv.img.endian);
	game_settings();
	return (0);
}

int	update(t_data *gd)
{
	// if (gd->state == 0)
	// 	main_menu(gd);
	// else if (gd->state == 1)
	// 	level_completed();
	// else if (gd->state == 2)
	// 	game_over(gd);
	// else if (gd->state == 3)
	// 	end_game(gd);
	// else if (gd->state == 4)
	// 	game(gd);
	// mlx_put_image_to_window(gd->mlx, gd->cnv.win, gd->cnv.img.ptr, 0, 0);
	game(gd);
	return (0);
}

int	main()
{
	t_data	this;

	awake(&this);

	mlx_hook(this.cnv.win, X_EVENT_KEY_PRESS, 0, &key_press, &this);
	mlx_hook(this.cnv.win, X_EVENT_KEY_RELEASE, 0, &key_release, &this);
	mlx_hook(this.cnv.win, X_EVENT_KEY_EXIT, 0, &close_window, &this);

	mlx_loop_hook(this.mlx, &update, &this);
	mlx_loop(this.mlx);

	return (0);
}

