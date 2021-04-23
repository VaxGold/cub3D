/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:37:17 by omercade          #+#    #+#             */
/*   Updated: 2021/04/21 18:42:13 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

t_texture	texture_save(t_data *gd, char *route)
{
	t_texture		tex;

	tex.img = mlx_xpm_file_to_image(gd->mlx, route,
			&tex.width, &tex.height);
	tex.addr = (int *)mlx_get_data_addr(tex.img,
			&tex.bits, &tex.line, &tex.endian);
	return (tex);
}
