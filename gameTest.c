/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameTest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 19:23:40 by omercade          #+#    #+#             */
/*   Updated: 2021/03/11 21:12:25 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//------------------------------------ DEFINES ------------------------------------//
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_RELEASE		3
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC					53
#define KEY_W					13
#define KEY_A					0
#define KEY_S					1
#define KEY_D					2
#define KEY_Q	    			12
#define KEY_E					14
#define KEY_TAB					48

//------------------------------------ GLOBAL VARIABLES ------------------------------------//
int worldMap [24][24] =
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

//------------------------------------ TOOLS ------------------------------------//
double  rad2deg_l(double n)
{
    double  res;
    int     laps;
    
    res = n * 180 / M_PI;
    laps = (int)res % 360;
	res -=	360 * laps;
    if (res < 0)
    {
        res += 360;
    }
    return (res);
}

void	clear_screen(t_data *gd)
{
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
}

//------------------------------------ INIT ------------------------------------//
void	game_init(t_data *gd)
{
	gd->game.scrW = 600;
	gd->game.scrH = 600;
	gd->game.mlx = mlx_init();
	gd->game.win = mlx_new_window(gd->game.mlx, gd->game.scrW, gd->game.scrH, "cubTestD");
	gd->game.img.img_ptr = mlx_new_image(gd->game.mlx, gd->game.scrW, gd->game.scrH);
	gd->game.img.data = (int *)mlx_get_data_addr(gd->game.img.img_ptr, &gd->game.img.bpp, &gd->game.img.size_l, &gd->game.img.endian);
}

//------------------------------------ KEY INPUT ------------------------------------//
int		key_press(int key_code, t_data *gd)
{
	printf("KEYCODE ----> %d\n", key_code);
	if (key_code == KEY_ESC)
        exit(0);
    else if (key_code == KEY_W)
        gd->player.mvFb = 1;
    else if (key_code == KEY_S)
        gd->player.mvFb = -1;
    else if (key_code == KEY_A)
        gd->player.mvRot = 1;
    else if (key_code == KEY_D)
        gd->player.mvRot = -1;
    else if (key_code == KEY_Q)
        gd->player.mvSide = -1;
    else if (key_code == KEY_E)
        gd->player.mvSide = 1;
	/*---PLAYER INFORMATION---*/
    else if (key_code == KEY_TAB)
    {
        printf("---------------- INFORMATION ----------------\n");
        printf("dirX----> %f, dirY----> %f\n", gd->player.dirX, gd->player.dirY);
        //printf("ANGLE-----> %f\n", inverse_angle(atan2(gd->player.dirX, gd->player.dirY) * 180 / M_PI));
    }
	return(0);
}

int		key_release(int key_code, t_data *gd)
{
	if (key_code == KEY_W)
        gd->player.mvFb = 0;
    else if (key_code == KEY_S)
        gd->player.mvFb = 0;
    else if (key_code == KEY_A)
        gd->player.mvRot = 0;
    else if (key_code == KEY_D)
        gd->player.mvRot = 0;
    else if (key_code == KEY_Q)
        gd->player.mvSide = 0;
    else if (key_code == KEY_E)
        gd->player.mvSide = 0;
	return(0);
}

/*int		close_game(t_data *gd);
{
	printf("%d x %d\n", gd->game.scrW, gd->game.scrH);
	exit(0);
}*/

//------------------------------------ RAYCASTING ------------------------------------//
void	step_dist(t_data *gd, int mapX, int mapY)
{
	if (gd->ray.dirX < 0)
	{
		gd->ray.stepX = -1;
        gd->ray.sideDistX = (gd->player.posX - mapX) * gd->ray.deltaDistX;
	}
	else
	{
		gd->ray.stepX = 1;
    	gd->ray.sideDistX = (mapX + 1.0 - gd->player.posX) * gd->ray.deltaDistX;
	}
	if (gd->ray.dirY < 0)
	{
		gd->ray.stepY = -1;
   		gd->ray.sideDistY = (gd->player.posY - mapY) * gd->ray.deltaDistY;
	}
	else
	{
		gd->ray.stepY = 1;
   		gd->ray.sideDistY = (mapY + 1.0 - gd->player.posY) * gd->ray.deltaDistY;
	}
	while (gd->ray.hit == 0)
	{
        if(gd->ray.sideDistX < gd->ray.sideDistY)
        {
        	gd->ray.sideDistX += gd->ray.deltaDistX;
          	mapX += gd->ray.stepX;
          	gd->ray.side = 0;
        }
        else
        {
          	gd->ray.sideDistY += gd->ray.deltaDistY;
          	mapY += gd->ray.stepY;
          	gd->ray.side = 1;
        }
        if(worldMap[mapX][mapY] > 0)
			gd->ray.hit = 1;
	}
}

void	img_draw(t_data *gd, int mapX, int mapY, int x)
{
	double perpWallDist;
    if (gd->ray.side == 0)
		perpWallDist = (mapX - gd->player.posX + (1- gd->ray.stepX) / 2) / gd->ray.dirX;
	else
		perpWallDist = (mapY - gd->player.posY + (1- gd->ray.stepY) / 2) / gd->ray.dirY;
		
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

    if (gd->ray.side == 1)
		rgb = rgb / 2;
    int pix = 0;
    while (pix < drawStart)
    {
        gd->game.img.data[pix * gd->game.scrH + x] = 0x02AFC4;
        pix++;
    }
    while (drawStart <= drawEnd)
	{
		gd->game.img.data[drawStart * gd->game.scrH + x] = rgb;
		drawStart++;
	}
    while (drawEnd <= gd->game.scrH)
    {
        gd->game.img.data[drawEnd * gd->game.scrH + x] = 0x386E39;
        drawEnd++;
    }
}

void	raycasting(t_data *gd)
{
	int x = 0;

	while (x <= gd->game.scrW)
	{
		double camX = 2 * x / (double) gd->game.scrW - 1;
		gd->ray.dirX = gd->player.dirX + gd->ray.planeX * camX;
		gd->ray.dirY = gd->player.dirY + gd->ray.planeY * camX;

		int mapX = (int)gd->player.posX;
		int mapY = (int)gd->player.posY;

		gd->ray.deltaDistX = fabs(1 / gd->ray.dirX);
		gd->ray.deltaDistY = fabs(1 / gd->ray.dirY);

		gd->ray.hit = 0;
		step_dist(gd, mapX, mapY);
		img_draw(gd, mapX, mapY, x);
		x++;
	}
}

//------------------------------------ TRANSFORMATIONS ------------------------------------//
void	motion(t_data *gd)
{
	//Rotation
	double oldDirX = gd->player.dirX;
    gd->player.dirX = gd->player.dirX * cos(gd->player.mvRot * gd->player.rotSpd) - gd->player.dirY * sin(gd->player.mvRot * gd->player.rotSpd);
    gd->player.dirY = oldDirX * sin(gd->player.mvRot * gd->player.rotSpd) + gd->player.dirY * cos(gd->player.mvRot * gd->player.rotSpd);
    double oldPlaneX = gd->ray.planeX;
    gd->ray.planeX = gd->ray.planeX * cos(gd->player.mvRot * gd->player.rotSpd) - gd->ray.planeY * sin(gd->player.mvRot * gd->player.rotSpd);
    gd->ray.planeY = oldPlaneX * sin(gd->player.mvRot * gd->player.rotSpd) + gd->ray.planeY * cos(gd->player.mvRot * gd->player.rotSpd);

	//Movement
	if (gd->player.mvFb != 0 && gd->player.mvSide != 0)
	{
		//Straight Movement
        if(worldMap[(int)(gd->player.posX + gd->player.mvFb * gd->player.dirX * gd->player.mvSpd)][(int)gd->player.posY] == 0)
        gd->player.posX = gd->player.posX + gd->player.mvFb * (gd->player.dirX * gd->player.mvSpd);
        //Side Movement
        if(worldMap[(int)gd->player.posX][(int)(gd->player.posY + gd->player.mvFb * gd->player.dirY * gd->player.mvSpd)] == 0)
        gd->player.posY = gd->player.posY + gd->player.mvFb * (gd->player.dirY * gd->player.mvSpd);
	}
	else
	{
		//Vector normalization
        if(worldMap[(int)(gd->player.posX + gd->player.mvFb * gd->player.dirX * gd->player.mvSpd)][(int)gd->player.posY] == 0)
        gd->player.posX = gd->player.posX + gd->player.mvFb * (gd->player.dirX * gd->player.mvSpd);
	}
}

//------------------------------------ MAIN ------------------------------------//
int		main_loop(t_data *gd)
{
	motion(gd);
	clear_screen(gd);
	raycasting(gd);
	mlx_put_image_to_window(gd->game.mlx, gd->game.win, gd->game.img.img_ptr, 0, 0);
	return(0);
}

int		main()
{
	t_data gd;

	//Player parameters
	gd.player.posX = 22, gd.player.posY = 12;
	gd.player.dirX = -1, gd.player.dirY = 0;
	gd.ray.planeX = 0, gd.ray.planeY = 0.66;
	gd.player.mvSpd = 0.5, gd.player.rotSpd = 0.1;

	//Game source inicialization
	game_init(&gd);

	//Update
	mlx_hook(gd.game.win, X_EVENT_KEY_PRESS, 0, &key_press, &gd);
	mlx_hook(gd.game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gd);
	//mlx_hook(gd.game.win, X_EVENT_KEY_EXIT, 0, &close_game, &gd);
	mlx_loop_hook(gd.game.mlx, &main_loop, &gd);
	mlx_loop(gd.game.mlx);

	return(0);
}