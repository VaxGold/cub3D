/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:05:55 by omercade          #+#    #+#             */
/*   Updated: 2021/04/06 18:02:26 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		awake(t_data *gd, char *arg)
{
	gd->mlx = mlx_init();
	if(ft_reader(gd, arg[1]) == -1)
		return(-1);
	gd->cnv.win = mlx_new_window(gd->mlx, gd->cnv.w, gd->cnv.h, "cub3D");
	gd->cnv.img.ptr = mlx_new_image(gd->mlx, gd->cnv.w, gd->cnv.h);
	gd->cnv.img.data = (int *)mlx_get_data_addr(gd->cnv.img.ptr, &gd->cnv.img.bpp, &gd->cnv.img.size_l, &gd->cnv.img.endian);
	return(0);
}

int     main(int nargs, char **xargs)
{
    t_data this;
	int		i;
	int		j;

	if (nargs == 2)
	{
		if (awake(&this, xargs[1]) == -1)
			exit(0);
		i = 0;
		printf("----------------------// MAP \\\\----------------------\n");
		while(i < this.map_h)
		{
			j = 0;
			while (j < this.map_w)
			{
				printf("%c", this.map[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
		printf("COLOR[0]------>0x%X, COLOR[1]------>0x%X\n", this.color[0], this.color[1]);
		printf("RESOLUTION: %d x %d\n", this.cnv.w, this.cnv.h);
	}
	else
	{
		error_display("ARGUMENTS");
		exit(0);
	}
	return(0);
}
