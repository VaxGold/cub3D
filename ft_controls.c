/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:04:27 by omercade          #+#    #+#             */
/*   Updated: 2021/03/18 20:44:40 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     close_game(t_data *gd)
{
    mlx_destroy_window(gd->game.mlx, gd->game.win);
    exit(0);
}

int     key_press(int key_code, t_data *gd)
{
    printf("KEYCODE ----> %d\n", key_code);
    if (key_code == KEY_ESC)
        exit(0);
    else if (key_code == KEY_W)
        gd->axis.x= 1;
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
    else if (key_code == KEY_TAB)
    {
        printf("---------------->| INFORMATION |<----------------\n");
        printf("dirX---> %f, dirY---> %f\n", gd->actor.dirX, gd->actor.dirY);
    }
    printf("AXIS(x, y): %f, %f\n", gd->axis.x, gd->axis.y);
    return(0);
}

int     key_release(int key_code, t_data *gd)
{
    if (key_code == KEY_W && gd->axis.x == 1)
        gd->axis.x= 0;
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
    return(0);
}

void    key_events(t_data *gd)
{
    mlx_hook(gd->game.win, X_EVENT_KEY_PRESS, 0, &key_press, &gd);
    mlx_hook(gd->game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gd);
    mlx_hook(gd->game.win, X_EVENT_KEY_EXIT, 0, &close_game, &gd);
}