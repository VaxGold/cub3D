/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:06 by omercade          #+#    #+#             */
/*   Updated: 2021/03/11 21:15:43 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC					53
#define KEY_W					13
#define KEY_A					0
#define KEY_S					1
#define KEY_D					2
#define KEY_Q	    			12
#define KEY_E					14

#define COLS					24
#define ROWS					24
#define TILE_SIZE				50
#define MOVSPEED                3
#define ROTSPEED                1

int worldMap [COLS][ROWS] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//------------------------------------ INIT ------------------------------------//
void    game_init(t_data *gd)
{
    printf("Loading window...\n");
    gd->game.scrW = 600;
    gd->game.scrH = 600;
    gd->game.mlx = mlx_init();
    gd->game.win = mlx_new_window(gd->game.mlx, gd->game.scrW, gd->game.scrH, "cubTestD");
    printf("Window loaded!\n");
    printf("Inicializating image...\n");
    gd->game.img.img_ptr = mlx_new_image(gd->game.mlx, gd->game.scrW, gd->game.scrH);
    gd->game.img.data = (int *)mlx_get_data_addr(gd->game.img.img_ptr, &gd->game.img.bpp, &gd->game.img.size_l, &gd->game.img.endian);
    printf("Image prepared!\n");
}

//------------------------------------ KEY_HOOK ------------------------------------//
int     deal_key(int key_code, t_data *gd)
{
    //double frameTime = (gd->game.time - gd->game.oldTime) / 1000;
    int i = 0;
    int j = 0;
    while (i <= gd->game.scrW)
    {
        j = 0;
        while (j <= gd->game.scrH)
        {
            gd->game.img.data[j * gd->game.scrW + i] = 0;
            j++;
        }
        i++;
    }
    if (key_code == KEY_ESC)
    {
        printf("Exit!\n");
        exit(0);
    }
    else if(key_code == KEY_W)
    {
        if(worldMap[(int)(gd->player.posX + gd->player.dirX * MOVSPEED)][(int)gd->player.posY] == 0)
            gd->player.posX += gd->player.dirX * MOVSPEED;
        if(worldMap[(int)gd->player.posX][(int)(gd->player.posY + gd->player.dirY * MOVSPEED)] == 0)
            gd->player.posY += gd->player.dirY * MOVSPEED;
    }
    else if(key_code == KEY_A)
    {
        double oldDirX = gd->player.dirX;
        gd->player.dirX = gd->player.dirX * cos(ROTSPEED) - gd->player.dirY * sin(ROTSPEED);
        gd->player.dirY = oldDirX * sin(ROTSPEED) + gd->player.dirY * cos(ROTSPEED);
        double oldPlaneX = gd->ray.planeX;
        gd->ray.planeX = gd->ray.planeX * cos(ROTSPEED) - gd->ray.planeY * sin(ROTSPEED);
        gd->ray.planeY = oldPlaneX * sin(ROTSPEED) + gd->ray.planeY * cos(ROTSPEED);
    }
    else if(key_code == KEY_S)
    {
        if(worldMap[(int)(gd->player.posX - gd->player.dirX * MOVSPEED)][(int)gd->player.posY] == 0)
            gd->player.posX -= gd->player.dirX * MOVSPEED;
        if(worldMap[(int)gd->player.posX][(int)(gd->player.posY - gd->player.dirY * MOVSPEED)] == 0)
            gd->player.posY -= gd->player.dirY * MOVSPEED;
    }
    else if(key_code == KEY_D)
    {
        double oldDirX = gd->player.dirX;
        gd->player.dirX = gd->player.dirX * cos(-ROTSPEED) - gd->player.dirY * sin(-ROTSPEED);
        gd->player.dirY = oldDirX * sin(-ROTSPEED) + gd->player.dirY * cos(-ROTSPEED);
        double oldPlaneX = gd->ray.planeX;
        gd->ray.planeX = gd->ray.planeX * cos(-ROTSPEED) - gd->ray.planeY * sin(-ROTSPEED);
        gd->ray.planeY = oldPlaneX * sin(-ROTSPEED) + gd->ray.planeY * cos(-ROTSPEED);
    }
    else if(key_code == KEY_Q)
    {
        printf("SIDELEFT\n");
    }
    else if(key_code == KEY_E)
    {
       printf("SIDERIGTH\n");
    }
    return(0);
}

//------------------------------------ LOOP ------------------------------------//
int     main_loop(t_data *gd)
{
    int x = 0;

    while (x < gd->game.scrW)
    {
        double cameraX = 2 * x / (double) gd->game.scrW - 1;
        double rayDirX = gd->player.dirX + gd->ray.planeX * cameraX;
		double rayDirY = gd->player.dirY + gd->ray.planeY * cameraX;

        int mapX = (int)gd->player.posX;
		int mapY = (int)gd->player.posY;

        double sideDistX;
		double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

        int stepX;
		int stepY;
		int hit = 0;
		int side;

        if (rayDirX < 0)
		{
			stepX = -1;
        	sideDistX = (gd->player.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
       		sideDistX = (mapX + 1.0 - gd->player.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
        	sideDistY = (gd->player.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
        	sideDistY = (mapY + 1.0 - gd->player.posY) * deltaDistY;
		}

        while (hit == 0)
		{
        	if(sideDistX < sideDistY)
        	{
        		sideDistX += deltaDistX;
          		mapX += stepX;
          		side = 0;
        	}
        	else
        	{
          		sideDistY += deltaDistY;
          		mapY += stepY;
          		side = 1;
        	}
        	if(worldMap[mapX][mapY] > 0)
				hit = 1;
		}

        if (side == 0)
			perpWallDist = (mapX - gd->player.posX + (1- stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - gd->player.posY + (1- stepY) / 2) / rayDirY;
		
		int lineHeight = (int) (gd->game.scrH / perpWallDist);

		int drawStart = -lineHeight / 2 + gd->game.scrH / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + gd->game.scrH / 2;
		if (drawEnd >= gd->game.scrH)
			drawEnd = gd->game.scrH - 1;

        int rgb;
		if (worldMap[mapX][mapY] == 1)
			rgb = 0xFF0000;
		else if (worldMap[mapX][mapY] == 2)
			rgb = 0x00FF00;
		else if (worldMap[mapX][mapY] == 3)
			rgb = 0x0000FF;
		else if (worldMap[mapX][mapY] == 4)
			rgb = 0xFFFFFF;
		else
			rgb = 0xFFFF00;

        if (side == 1)
			rgb = rgb / 2;
        int pix = 0;
        while (pix < drawStart)
        {
            gd->game.img.data[pix * gd->game.scrW + x] = 0x02AFC4;
            pix++;
        }
        while (drawStart <= drawEnd)
		{
			gd->game.img.data[drawStart * gd->game.scrW + x] = rgb;
			drawStart++;
		}
        while (drawEnd <= gd->game.scrH)
        {
            gd->game.img.data[drawEnd * gd->game.scrW + x] = 0x386E39;
            drawEnd++;
        }
		x++;
    }
    mlx_put_image_to_window(gd->game.mlx, gd->game.win, gd->game.img.img_ptr, 0, 0);
    return(0);
}

//------------------------------------ MAIN ------------------------------------//
int     main()
{
    t_data gd;

    gd.player.posX = 22, gd.player.posY = 12;
	gd.player.dirX = -1, gd.player.dirY = 0;
	gd.ray.planeX = 0, gd.ray.planeY = 0.66;

    printf("Starting game...\n");
    game_init(&gd);
    printf("Game loaded!\n");
    
    mlx_key_hook(gd.game.win, &deal_key, &gd);
    mlx_loop_hook(gd.game.mlx, &main_loop, &gd);
    mlx_loop(gd.game.mlx);
    return(0);
}