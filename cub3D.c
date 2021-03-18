/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:06 by omercade          #+#    #+#             */
/*   Updated: 2021/03/18 20:30:49 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//------------------------------------ AWAKE ------------------------------------//
void     awake(t_data *gd)
{
    gd->game.mlx = mlx_init();
    gd->game.win = mlx_new_window(gd->game.mlx, gd->game.scrW, gd->game.scrH, "cub3D");
    gd->game.img.ptr = mlx_new_image(gd->game.mlx, gd->game.scrW, gd->game.scrH);
    gd->game.img.data = (int *)mlx_get_data_addr(gd->game.img.ptr, &gd->game.img.bpp, &gd->game.img.size_l, &gd->game.img.endian);
}

//------------------------------------ EXIT ------------------------------------//
int     close_game(t_data *gd)
{
    mlx_destroy_window(gd->game.mlx, gd->game.win);
    exit(0);
}

//------------------------------------ UPDATE ------------------------------------//
int     update(t_data *gd)
{
    int x;

    ft_transform(gd);
    x = -1;
    while (++x < gd->game.scrW)
        ft_raycaster(gd, x);
    mlx_put_image_to_window(gd->game.mlx, gd->game.win, gd->game.img.ptr, 0, 0);
    return(0);
}

//------------------------------------ START ------------------------------------//
int     main(int nargs, char **xargs)
{
    t_data gd;

    if (nargs == 2 && nargs == 3)
    {
        //Map read
        //Player spawn
        //Texture loader
        //Game resources
        awake(&gd);
        if (nargs == 2)
        {
            key_events(&gd);
            mlx_loop_hook(gd.game.mlx, &update, &gd);
            mlx_loop(gd.game.mlx);
        }
        else if (nargs == 3 && xargs[1] /*== "--save"*/)
        {
            printf("CAPTURA DE PANTALLA!");
            close_game(&gd);
        }
    }
    return(0);
}