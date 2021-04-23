/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:08:39 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 20:56:18 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	close_window(t_data *gd)
{
	mlx_destroy_window(gd->mlx, gd->cnv.win);
	exit(0);
}

int	key_press(int key_code, t_data *gd)
{
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		gd->axis.x = 1;
	else if (key_code == KEY_S)
		gd->axis.x = -1;
	else if (key_code == KEY_A_LEFT)
		gd->axis.rot = 1;
	else if (key_code == KEY_A_RIGHT)
		gd->axis.rot = -1;
	else if (key_code == KEY_A)
		gd->axis.y = 1;
	else if (key_code == KEY_D)
		gd->axis.y = -1;
	return (0);
}

int	key_release(int key_code, t_data *gd)
{
	if (key_code == KEY_W && gd->axis.x == 1)
		gd->axis.x = 0;
	else if (key_code == KEY_S && gd->axis.x == -1)
		gd->axis.x = 0;
	else if (key_code == KEY_A_LEFT && gd->axis.rot == 1)
		gd->axis.rot = 0;
	else if (key_code == KEY_A_RIGHT && gd->axis.rot == -1)
		gd->axis.rot = 0;
	else if (key_code == KEY_A && gd->axis.y == 1)
		gd->axis.y = 0;
	else if (key_code == KEY_D && gd->axis.y == -1)
		gd->axis.y = 0;
	return (0);
}
