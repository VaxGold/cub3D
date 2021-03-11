# cub3D

My first game in C.

## PARA COMPILAR CON MINILIBX ##
gcc -L ../mlx -lmlx -framework OpenGL -framework AppKit [nombre del archivo]
gcc -L mlx -lmlx -framework OpenGL -framework AppKit cub3D.c


#------------------# TESTING #------------------#

void	raycasting(t_data *gd)
{
	int	check = 0;
	int cam;

	while (check < gd->game.scrW)
	{
		cam = 2 * check / (double) gd->game.scrW - 1;
		gd->ray.dirX = gd->player.dirX + gd->ray.planeX * cam;
		gd->ray.dirY = gd->player.dirY + gd->ray.planeY * cam;

		int mapX = (int)gd->player.posX;
		int mapY = (int)gd->player.posY;

		gd->ray.deltaDistX = fabs(1 / gd->ray.dirX);
		gd->ray.deltaDistY = fabs(1 / gd->ray.dirY);

		gd->ray.hit = 0;
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

        if (gd->ray.side == 0)
			gd->ray.perpWallDist = (mapX - gd->player.posX + (1 - gd->ray.stepX) / 2) / gd->ray.dirX;
		else
			gd->ray.perpWallDist = (mapY - gd->player.posY + (1 - gd->ray.stepY) / 2) / gd->ray.dirY;
		
		gd->ray.lineHeight = (int)(gd->game.scrH / gd->ray.perpWallDist);

		gd->ray.drawStart = -(gd->ray.lineHeight) / 2 + gd->game.scrH / 2;
		if (gd->ray.drawStart < 0)
			gd->ray.drawStart = 0;
		gd->ray.drawEnd = gd->ray.lineHeight / 2 + gd->game.scrH / 2;
		if (gd->ray.drawEnd >= gd->game.scrH)
			gd->ray.drawEnd = gd->game.scrH - 1;

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
        while (pix < gd->ray.drawStart)
        {
            gd->game.img.data[pix * gd->game.scrW + check] = 0x02AFC4;
            pix++;
        }
        while (gd->ray.drawStart <= gd->ray.drawEnd)
		{
			gd->game.img.data[gd->ray.drawStart * gd->game.scrW + check] = rgb;
			gd->ray.drawStart++;
		}
        while (gd->ray.drawEnd <= gd->game.scrH)
        {
            gd->game.img.data[gd->ray.drawEnd * gd->game.scrW + check] = 0x386E39;
            gd->ray.drawEnd++;
        }
		check++;
	}
}