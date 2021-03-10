/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:08:06 by omercade          #+#    #+#             */
/*   Updated: 2021/03/09 17:29:51 by omercade         ###   ########.fr       */
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
void    game_init(t_all *gdat)
{
    printf("Loading window...\n");
    gdat->game.screen_w = 600;
    gdat->game.screen_h = 600;
    gdat->game.mlx = mlx_init();
    gdat->game.win = mlx_new_window(gdat->game.mlx, gdat->game.screen_w, gdat->game.screen_h, "cubTestD");
    printf("Window loaded!\n");
    printf("Inicializating image...\n");
    gdat->game.img.img_ptr = mlx_new_image(gdat->game.mlx, gdat->game.screen_w, gdat->game.screen_h);
    gdat->game.img.data = (int *)mlx_get_data_addr(gdat->game.img.img_ptr, &gdat->game.img.bpp, &gdat->game.img.size_l, &gdat->game.img.endian);
    printf("Image prepared!\n");
}

//------------------------------------ KEY_HOOK ------------------------------------//
int     deal_key(int key_code, t_all *gdat)
{
    double frameTime = (gdat->game.time - gdat->game.oldTime) / 1000;
    int i = 0;
    int j = 0;
    while (i <= gdat->game.screen_w)
    {
        j = 0;
        while (j <= gdat->game.screen_h)
        {
            gdat->game.img.data[j * gdat->game.screen_w + i] = 0;
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
        if(worldMap[(int)(gdat->player.posX + gdat->player.dirX * MOVSPEED)][(int)gdat->player.posY] == 0)
            gdat->player.posX += gdat->player.dirX * MOVSPEED;
        if(worldMap[(int)gdat->player.posX][(int)(gdat->player.posY + gdat->player.dirY * MOVSPEED)] == 0)
            gdat->player.posY += gdat->player.dirY * MOVSPEED;
    }
    else if(key_code == KEY_A)
    {
        double oldDirX = gdat->player.dirX;
        gdat->player.dirX = gdat->player.dirX * cos(ROTSPEED) - gdat->player.dirY * sin(ROTSPEED);
        gdat->player.dirY = oldDirX * sin(ROTSPEED) + gdat->player.dirY * cos(ROTSPEED);
        double oldPlaneX = gdat->player.planeX;
        gdat->player.planeX = gdat->player.planeX * cos(ROTSPEED) - gdat->player.planeY * sin(ROTSPEED);
        gdat->player.planeY = oldPlaneX * sin(ROTSPEED) + gdat->player.planeY * cos(ROTSPEED);
    }
    else if(key_code == KEY_S)
    {
        if(worldMap[(int)(gdat->player.posX - gdat->player.dirX * MOVSPEED)][(int)gdat->player.posY] == 0)
            gdat->player.posX -= gdat->player.dirX * MOVSPEED;
        if(worldMap[(int)gdat->player.posX][(int)(gdat->player.posY - gdat->player.dirY * MOVSPEED)] == 0)
            gdat->player.posY -= gdat->player.dirY * MOVSPEED;
    }
    else if(key_code == KEY_D)
    {
        double oldDirX = gdat->player.dirX;
        gdat->player.dirX = gdat->player.dirX * cos(-ROTSPEED) - gdat->player.dirY * sin(-ROTSPEED);
        gdat->player.dirY = oldDirX * sin(-ROTSPEED) + gdat->player.dirY * cos(-ROTSPEED);
        double oldPlaneX = gdat->player.planeX;
        gdat->player.planeX = gdat->player.planeX * cos(-ROTSPEED) - gdat->player.planeY * sin(-ROTSPEED);
        gdat->player.planeY = oldPlaneX * sin(-ROTSPEED) + gdat->player.planeY * cos(-ROTSPEED);
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
int     main_loop(t_all *gdat)
{
    int x = 0;

    while (x < gdat->game.screen_w)
    {
        double cameraX = 2 * x / (double) gdat->game.screen_w - 1;
        double rayDirX = gdat->player.dirX + gdat->player.planeX * cameraX;
		double rayDirY = gdat->player.dirY + gdat->player.planeY * cameraX;

        int mapX = (int)gdat->player.posX;
		int mapY = (int)gdat->player.posY;

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
        	sideDistX = (gdat->player.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
       		sideDistX = (mapX + 1.0 - gdat->player.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
        	sideDistY = (gdat->player.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
        	sideDistY = (mapY + 1.0 - gdat->player.posY) * deltaDistY;
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
			perpWallDist = (mapX - gdat->player.posX + (1- stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - gdat->player.posY + (1- stepY) / 2) / rayDirY;
		
		int lineHeight = (int) (gdat->game.screen_h / perpWallDist);

		int drawStart = -lineHeight / 2 + gdat->game.screen_h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + gdat->game.screen_h / 2;
		if (drawEnd >= gdat->game.screen_h)
			drawEnd = gdat->game.screen_h - 1;

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
            gdat->game.img.data[pix * gdat->game.screen_w + x] = 0x02AFC4;
            pix++;
        }
        while (drawStart <= drawEnd)
		{
			gdat->game.img.data[drawStart * gdat->game.screen_w + x] = rgb;
			drawStart++;
		}
        while (drawEnd <= gdat->game.screen_h)
        {
            gdat->game.img.data[drawEnd * gdat->game.screen_w + x] = 0x386E39;
            drawEnd++;
        }
		x++;
    }
    mlx_put_image_to_window(gdat->game.mlx, gdat->game.win, gdat->game.img.img_ptr, 0, 0);
    return(0);
}

//------------------------------------ MAIN ------------------------------------//
int     main()
{
    t_all gdat;

    gdat.player.posX = 22, gdat.player.posY = 12;
	gdat.player.dirX = -1, gdat.player.dirY = 0;
	gdat.player.planeX = 0, gdat.player.planeY = 0.66;
    gdat.game.time = 0, gdat.game.oldTime = 0;

    printf("Starting game...\n");
    game_init(&gdat);
    printf("Game loaded!\n");
    
    mlx_key_hook(gdat.game.win, &deal_key, &gdat);
    mlx_loop_hook(gdat.game.mlx, &main_loop, &gdat);
    mlx_loop(gdat.game.mlx);
    return(0);
}