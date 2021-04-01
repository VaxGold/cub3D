/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:05:55 by omercade          #+#    #+#             */
/*   Updated: 2021/04/01 21:40:54 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	awake(t_data *gd)
{
	gd->mlx = mlx_init();
	gd->cnv.win = mlx_new_window(gd->mlx, gd->cnv.w, gd->cnv.h, "cub3D");
	gd->cnv.img.ptr = mlx_new_image(gd->mlx, gd->cnv.w, gd->cnv.h);
	gd->cnv.img.data = (int *)mlx_get_data_addr(gd->cnv.img.ptr, &gd->cnv.img.bpp, &gd->cnv.img.size_l, &gd->cnv.img.endian);
}

int     main(int nargs, char **xargs)
{
    t_data this;
	int		i;
	int		j;

	if (nargs == 2)
	{
		awake(&this);
		if(ft_reader(&this, xargs[1]))
		{
			printf("EXIT!!\n");
			exit(0);
		}
		i = 0;
		printf("----------------------// MAP \\----------------------\n");
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
		printf("COLOR[0]------>0x%x, COLOR[1]------>0x%X\n", this.color[0], this.color[1]);
		printf("RESOLUTION: %d x %d\n", this.cnv.w, this.cnv.h);
	}
	else
	{
		error_display("ARGUMENTS");
		exit(0);
	}
	return(0);
}
