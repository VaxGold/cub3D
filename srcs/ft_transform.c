/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:17:01 by omercade          #+#    #+#             */
/*   Updated: 2021/03/17 19:36:12 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void    ft_yaw(t_data *gd)
{
    double  oldDirX;
    
    oldDirX = gd->actor.dirX;
    gd->actor.dirX = gd->actor.dirX * cos(gd->axis.rot * gd->actor.rotSpd) - gd->actor.dirY * sin(gd->axis.rot * gd->actor.rotSpd);
    gd->actor.dirY = oldDirX * sin(gd->axis.rot * gd->actor.rotSpd) + gd->actor.dirY * cos(gd->axis.rot * gd->actor.rotSpd);
    oldDirX = gd->actor.planeX;
    gd->actor.planeX = gd->actor.planeX * cos(gd->axis.rot * gd->actor.rotSpd) - gd->actor.planeY * sin(gd->axis.rot * gd->actor.rotSpd);
    gd->actor.planeY = oldDirX * sin(gd->axis.rot * gd->actor.rotSpd) + gd->actor.planeY * cos(gd->axis.rot * gd->actor.rotSpd);
}

void    ft_displacement(t_data *gd)
{
    double  normalX;
    double  normalY;

    if(gd->game.map[(int)(gd->actor.posX + gd->axis.x * gd->actor.dirX * gd->actor.mvSpd)][(int)gd->actor.posY] == 0)
        gd->actor.posX = gd->actor.posX + gd->axis.x * (gd->actor.dirX * gd->actor.mvSpd);
    if(gd->game.map[(int)gd->actor.posX][(int)(gd->actor.posY + gd->axis.x * gd->actor.dirY * gd->actor.mvSpd)] == 0)
        gd->actor.posY = gd->actor.posY + gd->axis.x * (gd->actor.dirY * gd->actor.mvSpd);
    if(gd->game.map[(int)(gd->actor.posX + gd->axis.y * normalX * gd->actor.mvSpd)][(int)gd->actor.posY] == 0)
        gd->actor.posX = gd->actor.posX + gd->axis.y * (normalX * gd->actor.mvSpd);
    if(gd->game.map[(int)gd->actor.posX][(int)(gd->actor.posY + gd->axis.y * normalY * gd->actor.mvSpd)] == 0)
        gd->actor.posY = gd->actor.posY + gd->axis.y * (normalY * gd->actor.mvSpd);  
}

void    ft_transform(t_data *gd)
{
    gd->actor.rotSpd = ROTSPEED;
    ft_yaw(gd);
    if (gd->axis.x != 0 && gd->axis.y != 0)
        gd->actor.mvSpd = MOVSPEED * (sqrt(2)/ 2);
    else
        gd->actor.mvSpd = MOVSPEED;
    ft_displacement(gd);
}