/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:37:01 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 19:52:45 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

"../cub3D_bonus.h"

int	game_over(t_data *gd)
{
	int		x;

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

