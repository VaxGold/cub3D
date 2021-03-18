#include "cub3D.h"

//------------------------------------ MAP ------------------------------------//
int worldMap [COLS][ROWS] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//------------------------------------ TOOLS ------------------------------------//
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


//------------------------------------ START ------------------------------------//
void     game_init(t_data *gd)
{
    //Set resolution
    gd->game.scrW = 600;
    gd->game.scrH = 600;

    gd->game.mlx = mlx_init();
    gd->game.win = mlx_new_window(gd->game.mlx, gd->game.scrW, gd->game.scrH, "cub3D");
    gd->game.img.ptr = mlx_new_image(gd->game.mlx, gd->game.scrW, gd->game.scrH);
    gd->game.img.data = (int *)mlx_get_data_addr(gd->game.img.ptr, &gd->game.img.bpp, &gd->game.img.size_l, &gd->game.img.endian);
}

void    texture_generator(t_data *gd)
{
    gd->txtr.img = mlx_xpm_file_to_image(gd->game.mlx, "srcs/imgs/bluestone.xpm", &gd->txtW, &gd->txtH);
    gd->txtr.addr = (int *)mlx_get_data_addr(gd->txtr.img, &gd->txtr.bits, &gd->txtr.line, &gd->txtr.endian);
}

//------------------------------------ KEY INPUT ------------------------------------//
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
    else if (key_code == KEY_L_SHFT)
        gd->axis.run = 3;
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
    else if (key_code == KEY_L_SHFT)
        gd->axis.run = 1;
    return(0);
}

int     close_game(t_data *gd)
{
    //free(gd->txtr);
    mlx_destroy_window(gd->game.mlx, gd->game.win);
    exit(0);
}

//------------------------------------ TRANSFORM ------------------------------------//
void    ft_transforms(t_data *gd)
{
    double  normalX;
    double  normalY;
    double  oldDirX;
    double  temp;
    
    //Rotation
    oldDirX = gd->actor.dirX;
    gd->actor.dirX = gd->actor.dirX * cos(gd->axis.rot * ROTSPEED) - gd->actor.dirY * sin(gd->axis.rot * ROTSPEED);
    gd->actor.dirY = oldDirX * sin(gd->axis.rot * ROTSPEED) + gd->actor.dirY * cos(gd->axis.rot * ROTSPEED);
    oldDirX = gd->actor.planeX;
    gd->actor.planeX = gd->actor.planeX * cos(gd->axis.rot * ROTSPEED) - gd->actor.planeY * sin(gd->axis.rot * ROTSPEED);
    gd->actor.planeY = oldDirX * sin(gd->axis.rot * ROTSPEED) + gd->actor.planeY * cos(gd->axis.rot * ROTSPEED);
    
    //Displacement
    if (gd->axis.x != 0 && gd->axis.y != 0)
        temp = gd->axis.run * MOVSPEED * (sqrt(2)/ 2);
    else
        temp = gd->axis.run * MOVSPEED;
    normalX = gd->actor.dirX * cos(90 * M_PI / 180) - gd->actor.dirY * sin(90 * M_PI / 180);
    normalY = gd->actor.dirX * sin(90 * M_PI / 180) + gd->actor.dirY * cos(90 * M_PI / 180);
    if(worldMap[(int)(gd->actor.posX + gd->axis.x * gd->actor.dirX * temp)][(int)gd->actor.posY] == 0)
        gd->actor.posX = gd->actor.posX + gd->axis.x * (gd->actor.dirX * temp);
    if(worldMap[(int)gd->actor.posX][(int)(gd->actor.posY + gd->axis.x * gd->actor.dirY * temp)] == 0)
        gd->actor.posY = gd->actor.posY + gd->axis.x * (gd->actor.dirY * temp);
    if(worldMap[(int)(gd->actor.posX + gd->axis.y * normalX * temp)][(int)gd->actor.posY] == 0)
        gd->actor.posX = gd->actor.posX + gd->axis.y * (normalX * temp);
    if(worldMap[(int)gd->actor.posX][(int)(gd->actor.posY + gd->axis.y * normalY * temp)] == 0)
        gd->actor.posY = gd->actor.posY + gd->axis.y * (normalY * temp);
}

//------------------------------------ RAYCASTING ------------------------------------//
void    ft_raycasting(t_data *gd, int x)
{
    double cameraX = 2 * x / (double) gd->game.scrW - 1;
        double rayDirX = gd->actor.dirX + gd->actor.planeX * cameraX;
		double rayDirY = gd->actor.dirY + gd->actor.planeY * cameraX;

        int mapX = (int)gd->actor.posX;
		int mapY = (int)gd->actor.posY;

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
        	sideDistX = (gd->actor.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
       		sideDistX = (mapX + 1.0 - gd->actor.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
        	sideDistY = (gd->actor.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
        	sideDistY = (mapY + 1.0 - gd->actor.posY) * deltaDistY;
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
			perpWallDist = (mapX - gd->actor.posX + (1- stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - gd->actor.posY + (1- stepY) / 2) / rayDirY;
		
		int lineHeight = (int) (gd->game.scrH / perpWallDist);

		int drawStart = -lineHeight / 2 + gd->game.scrH / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + gd->game.scrH / 2;
		if (drawEnd >= gd->game.scrH)
			drawEnd = gd->game.scrH - 1;

        //int texNum = worldMap[mapX][mapY] - 1;

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if(side == 0)
            wallX = gd->actor.posY + perpWallDist * rayDirY;
        else
            wallX = gd->actor.posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        //x coordinate on the texture
        int texX = (int)(wallX * (double)gd->txtW);
        if(side == 0 && rayDirX > 0)
            texX = gd->txtW - texX - 1;
        if(side == 1 && rayDirY < 0)
            texX = gd->txtW - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * gd->txtH / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - gd->game.scrH / 2 + lineHeight / 2) * step;

        int pix = 0;
        while (pix < drawStart)
        {
            gd->game.img.data[pix * gd->game.scrW + x] = 0x02AFC4;
            pix++;
        }
        int *textn = gd->txtr.addr;
        pix = drawStart;
        while (pix < drawEnd)
		{
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (gd->txtH - 1);
            //printf("TexY-->%d, texH--->%d\n", texY, gd->txtH);
            texPos += step;
            int color = textn[gd->txtH * texY + texX];
            //int color = 0xFF0000;
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(side == 1)
                color = (color >> 1) & 8355711;
			gd->game.img.data[pix * gd->game.scrW + x] = color;
			pix++;
		}
        while (drawEnd <= gd->game.scrH)
        {
            gd->game.img.data[drawEnd * gd->game.scrW + x] = 0x386E39;
            drawEnd++;
        }
}

//------------------------------------ UPDATE ------------------------------------//
int     update(t_data *gd)
{
    int x = 0;

    ft_transforms(gd);
    while (x < gd->game.scrW)
    {
        ft_raycasting(gd, x);
        x++;
    }
    mlx_put_image_to_window(gd->game.mlx, gd->game.win, gd->game.img.ptr, 0, 0);
    return(0);
}

//------------------------------------ AWAKE ------------------------------------//
int     main(/*int nargs, char **xargs*/)
{
    t_data gd;
    
    //Player spawn
    gd.actor.posX = 22, gd.actor.posY = 12;
	gd.actor.dirX = -1, gd.actor.dirY = 0;
	gd.actor.planeX = 0, gd.actor.planeY = 0.66;
    
    //Game resources
    game_init(&gd);
    gd.txtH = 100, gd.txtW = 100;
    texture_generator(&gd);

    //Input events
    mlx_hook(gd.game.win, X_EVENT_KEY_PRESS, 0, &key_press, &gd);
    mlx_hook(gd.game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gd);
    mlx_hook(gd.game.win, X_EVENT_KEY_EXIT, 0, &close_game, &gd);


    //Starting update
    mlx_loop_hook(gd.game.mlx, &update, &gd);
    mlx_loop(gd.game.mlx);

    return(0);
}