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

double angle_laps(double a)
{
    int laps;

    laps = (int)a % 360;
    return(a - 360 * laps);
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
int     key_press(int key_code, t_all *gdat)
{
    //double frameTime = (gdat->game.time - gdat->game.oldTime) / 1000;
    printf("KEYCODE ----> %d\n", key_code);
    
    if (key_code == KEY_ESC)
    {
        printf("Exit!\n");
        exit(0);
    }
    else if (key_code == KEY_W)
    {
        gdat->player.move.fb = 1;
    }
    else if (key_code == KEY_S)
    {
        gdat->player.move.fb = -1;
    }
    else if (key_code == KEY_A)
    {
        gdat->player.move.rot = 1;
    }
    else if (key_code == KEY_D)
    {
        gdat->player.move.rot = -1;
    }
    else if (key_code == KEY_Q)
    {
        gdat->player.move.rl = -1;
    }
    else if (key_code == KEY_E)
    {
        gdat->player.move.rl = 1;
    }
    else if (key_code == KEY_TAB)
    {
        printf("---------------- INFORMATION ----------------\n");
        printf("dirX----> %f, dirY----> %f\n", gdat->player.dirX, gdat->player.dirY);
        printf("ANGLE-----> %f\n", atan(gdat->player.dirX / gdat->player.dirY));
    }
    
    return(0);
}

int     key_release(int key_code, t_all *gdat)
{
    if (key_code == KEY_W)
    {
        gdat->player.move.fb = 0;
    }
    else if (key_code == KEY_S)
    {
        gdat->player.move.fb = 0;
    }
    else if (key_code == KEY_A)
    {
        gdat->player.move.rot = 0;
    }
    else if (key_code == KEY_D)
    {
        gdat->player.move.rot = 0;
    }
    else if (key_code == KEY_Q)
    {
        gdat->player.move.rl = 0;
    }
    else if (key_code == KEY_E)
    {
        gdat->player.move.rl = 0;
    }
    return(0);
}

//------------------------------------ CLEAR SCREEN ------------------------------------//
void    clear_screen(t_all *gdat)
{
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
}

//------------------------------------ LOOP ------------------------------------//

void    ft_movement(t_all *gdat)
{
    //ROTATION
    double oldDirX = gdat->player.dirX;
    gdat->player.dirX = gdat->player.dirX * cos(gdat->player.move.rot * ROTSPEED) - gdat->player.dirY * sin(gdat->player.move.rot * ROTSPEED);
    gdat->player.dirY = oldDirX * sin(gdat->player.move.rot * ROTSPEED) + gdat->player.dirY * cos(gdat->player.move.rot * ROTSPEED);
    double oldPlaneX = gdat->player.planeX;
    gdat->player.planeX = gdat->player.planeX * cos(gdat->player.move.rot * ROTSPEED) - gdat->player.planeY * sin(gdat->player.move.rot * ROTSPEED);
    gdat->player.planeY = oldPlaneX * sin(gdat->player.move.rot * ROTSPEED) + gdat->player.planeY * cos(gdat->player.move.rot * ROTSPEED);

    //MOVEMENT

    /*if(gdat->player.move.rl != 0 && gdat->player.move.fb != 0)
    {
        //Straight Movement
        if(worldMap[(int)(gdat->player.posX + gdat->player.move.fb * gdat->player.dirX * MOVSPEED)][(int)gdat->player.posY] == 0)
        gdat->player.posX = gdat->player.posX + gdat->player.move.fb * (gdat->player.dirX * MOVSPEED);
        //Side Movement
        if(worldMap[(int)gdat->player.posX][(int)(gdat->player.posY + gdat->player.move.fb * gdat->player.dirY * MOVSPEED)] == 0)
        gdat->player.posY = gdat->player.posY + gdat->player.move.fb * (gdat->player.dirY * MOVSPEED);
    }
    else
    {
        if(worldMap[(int)(gdat->player.posX + gdat->player.move.fb * gdat->player.dirX * MOVSPEED)][(int)gdat->player.posY] == 0)
        gdat->player.posX = gdat->player.posX + gdat->player.move.fb * (gdat->player.dirX * MOVSPEED);
    }*/
    
    if(worldMap[(int)(gdat->player.posX + gdat->player.move.fb * gdat->player.dirX * MOVSPEED)][(int)gdat->player.posY] == 0)
        gdat->player.posX = gdat->player.posX + gdat->player.move.fb * (gdat->player.dirX * MOVSPEED);
    if(worldMap[(int)gdat->player.posX][(int)(gdat->player.posY + gdat->player.move.fb * gdat->player.dirY * MOVSPEED)] == 0)
        gdat->player.posY = gdat->player.posY + gdat->player.move.fb * (gdat->player.dirY * MOVSPEED);

    if(worldMap[(int)(gdat->player.posX + gdat->player.move.fb * gdat->player.dirX * MOVSPEED)][(int)gdat->player.posY] == 0)
        gdat->player.posX = gdat->player.posX + gdat->player.move.fb * (gdat->player.dirX * MOVSPEED);
    if(worldMap[(int)gdat->player.posX][(int)(gdat->player.posY + gdat->player.move.fb * gdat->player.dirY * MOVSPEED)] == 0)
        gdat->player.posY = gdat->player.posY + gdat->player.move.fb * (gdat->player.dirY * MOVSPEED);
}
int     main_loop(t_all *gdat)
{
    int x = 0;

    ft_movement(gdat);
    clear_screen(gdat);
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
    
    //mlx_key_hook(gdat.game.win, &deal_key, &gdat);
    mlx_hook(gdat.game.win, X_EVENT_KEY_PRESS, 0, &key_press, &gdat);
    mlx_hook(gdat.game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gdat);
    mlx_loop_hook(gdat.game.mlx, &main_loop, &gdat);
    mlx_loop(gdat.game.mlx);
    return(0);
}