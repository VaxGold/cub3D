#include "cub3D.h"

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

#define COLS					24
#define ROWS					24
#define TILE_SIZE				50
#define MOVSPEED                0.2
#define ROTSPEED                0.1

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

double angle_laps(double a)
{
    int laps;

    laps = (int)a % 360;
    return(a - 360 * laps);
}

double  inverse_angle(double a)
{
    if (a < 0)
    {
        a += 360;
    }
    return(a);
}

double  rad_to_deg(double n)
{
    double  res;
    int     lap;
    
    res = n * 180 / M_PI;
    res = angle_laps(res);
    if (res < 0)
    {
        res += 360;
    }
    return (res);
}
//------------------------------------ KEY_HOOK ------------------------------------//
int     key_press(int key_code, t_data *gd)
{
    //double frameTime = (gd->game.time - gd->game.oldTime) / 1000;
    printf("KEYCODE ----> %d\n", key_code);
    
    if (key_code == KEY_ESC)
    {
        printf("Exit!\n");
        exit(0);
    }
    else if (key_code == KEY_W)
    {
        gd->player.mvFb = 1;
    }
    else if (key_code == KEY_S)
    {
        gd->player.mvFb = -1;
    }
    else if (key_code == KEY_A)
    {
        gd->player.mvRot = 1;
    }
    else if (key_code == KEY_D)
    {
        gd->player.mvRot = -1;
    }
    else if (key_code == KEY_Q)
    {
        gd->player.mvSide = -1;
    }
    else if (key_code == KEY_E)
    {
        gd->player.mvSide = 1;
    }
    else if (key_code == KEY_TAB)
    {
        printf("---------------- INFORMATION ----------------\n");
        printf("dirX----> %f, dirY----> %f\n", gd->player.dirX, gd->player.dirY);
        printf("ANGLE-----> %f\n", inverse_angle(atan2(gd->player.dirX, gd->player.dirY) * 180 / M_PI));
    }
    
    return(0);
}

int     key_release(int key_code, t_data *gd)
{
    if (key_code == KEY_W)
    {
        gd->player.mvFb = 0;
    }
    else if (key_code == KEY_S)
    {
        gd->player.mvFb = 0;
    }
    else if (key_code == KEY_A)
    {
        gd->player.mvRot = 0;
    }
    else if (key_code == KEY_D)
    {
        gd->player.mvRot = 0;
    }
    else if (key_code == KEY_Q)
    {
        gd->player.mvSide = 0;
    }
    else if (key_code == KEY_E)
    {
        gd->player.mvSide = 0;
    }
    return(0);
}

//------------------------------------ CLEAR SCREEN ------------------------------------//
void    clear_screen(t_data *gd)
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

//------------------------------------ LOOP ------------------------------------//

void    ft_movement(t_data *gd)
{
    //ROTATION
    double oldDirX = gd->player.dirX;
    gd->player.dirX = gd->player.dirX * cos(gd->player.mvRot * ROTSPEED) - gd->player.dirY * sin(gd->player.mvRot * ROTSPEED);
    gd->player.dirY = oldDirX * sin(gd->player.mvRot * ROTSPEED) + gd->player.dirY * cos(gd->player.mvRot * ROTSPEED);
    double oldPlaneX = gd->ray.planeX;
    gd->ray.planeX = gd->ray.planeX * cos(gd->player.mvRot * ROTSPEED) - gd->ray.planeY * sin(gd->player.mvRot * ROTSPEED);
    gd->ray.planeY = oldPlaneX * sin(gd->player.mvRot * ROTSPEED) + gd->ray.planeY * cos(gd->player.mvRot * ROTSPEED);

    //MOVEMENT

    /*if(gd->playermvSide != 0 && gd->playermvFb != 0)
    {
        //Straight Movement
        if(worldMap[(int)(gd->player.posX + gd->playermvFb * gd->player.dirX * MOVSPEED)][(int)gd->player.posY] == 0)
        gd->player.posX = gd->player.posX + gd->playermvFb * (gd->player.dirX * MOVSPEED);
        //Side Movement
        if(worldMap[(int)gd->player.posX][(int)(gd->player.posY + gd->playermvFb * gd->player.dirY * MOVSPEED)] == 0)
        gd->player.posY = gd->player.posY + gd->playermvFb * (gd->player.dirY * MOVSPEED);
    }
    else
    {
        if(worldMap[(int)(gd->player.posX + gd->playermvFb * gd->player.dirX * MOVSPEED)][(int)gd->player.posY] == 0)
        gd->player.posX = gd->player.posX + gd->playermvFb * (gd->player.dirX * MOVSPEED);
    }*/
    
    if(worldMap[(int)(gd->player.posX + gd->player.mvFb * gd->player.dirX * MOVSPEED)][(int)gd->player.posY] == 0)
        gd->player.posX = gd->player.posX + gd->player.mvFb * (gd->player.dirX * MOVSPEED);
    if(worldMap[(int)gd->player.posX][(int)(gd->player.posY + gd->player.mvFb * gd->player.dirY * MOVSPEED)] == 0)
        gd->player.posY = gd->player.posY + gd->player.mvFb * (gd->player.dirY * MOVSPEED);

    if(worldMap[(int)(gd->player.posX + gd->player.mvFb * gd->player.dirX * MOVSPEED)][(int)gd->player.posY] == 0)
        gd->player.posX = gd->player.posX + gd->player.mvFb * (gd->player.dirX * MOVSPEED);
    if(worldMap[(int)gd->player.posX][(int)(gd->player.posY + gd->player.mvFb * gd->player.dirY * MOVSPEED)] == 0)
        gd->player.posY = gd->player.posY + gd->player.mvFb * (gd->player.dirY * MOVSPEED);
}
int     main_loop(t_data *gd)
{
    int x = 0;

    ft_movement(gd);
    clear_screen(gd);
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
    
    //mlx_key_hook(gd.game.win, &deal_key, &gd);
    mlx_hook(gd.game.win, X_EVENT_KEY_PRESS, 0, &key_press, &gd);
    mlx_hook(gd.game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gd);
    mlx_loop_hook(gd.game.mlx, &main_loop, &gd);
    mlx_loop(gd.game.mlx);
    return(0);
}