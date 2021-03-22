/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:17:58 by omercade          #+#    #+#             */
/*   Updated: 2021/03/18 21:25:02 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    init_tex(t_data *gd)
{
    int i;

    i = 0;
    while (i < 4)
    {
        gd->texs[i].width = gd->txtW;
        gd->texs[i].height = gd->txtH;
        gd->texs[i].img = mlx_xpm_file_to_image(gd->game.mlx, "./ruta", &gd->texs[i].width, &gd->texs[i].height);
        gd->texs[i].addr = (int *)mlx_get_data_addr(gd->texs[i].img, &gd->texs[i].bits, &gd->texs[i].line, &gd->texs[i].endian);
    }
}