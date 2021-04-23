/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:17:49 by omercade          #+#    #+#             */
/*   Updated: 2021/04/13 19:44:30 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	bmp_info(t_bmp *bmp, t_data *gd)
{
	bmp->bmpfileheader = (unsigned char *)malloc(14);
	bmp->bmpinfoheader = (unsigned char *)malloc(40);
	ft_memset(bmp->bmpfileheader, 0, 16);
	ft_memset(bmp->bmpinfoheader, 0, 40);
	bmp->bmpfileheader[0] = 'B';
	bmp->bmpfileheader[1] = 'M';
	bmp->bmpfileheader[2] = (unsigned char)(bmp->filesize);
	bmp->bmpfileheader[3] = (unsigned char)(bmp->filesize >> 8);
	bmp->bmpfileheader[4] = (unsigned char)(bmp->filesize >> 16);
	bmp->bmpfileheader[5] = (unsigned char)(bmp->filesize >> 24);
	bmp->bmpfileheader[10] = 54;
	bmp->bmpinfoheader[0] = 40;
	bmp->bmpinfoheader[12] = 1;
	bmp->bmpinfoheader[14] = 24;
	bmp->bmpinfoheader[4] = (unsigned char)(gd->cnv.w);
	bmp->bmpinfoheader[5] = (unsigned char)(gd->cnv.w >> 8);
	bmp->bmpinfoheader[6] = (unsigned char)(gd->cnv.w >> 16);
	bmp->bmpinfoheader[7] = (unsigned char)(gd->cnv.w >> 24);
	bmp->bmpinfoheader[8] = (unsigned char)(gd->cnv.h);
	bmp->bmpinfoheader[9] = (unsigned char)(gd->cnv.h >> 8);
	bmp->bmpinfoheader[10] = (unsigned char)(gd->cnv.h >> 16);
	bmp->bmpinfoheader[11] = (unsigned char)(gd->cnv.h >> 24);
	bmp->bmppad = (unsigned char *)malloc(3);
	ft_memset(bmp->bmppad, 0, 3);
}

void	fill_bmp(t_bmp *bmp, t_data *gd)
{
	bmp->fd = open
		("./srcs/imgs/screenshoots/sc.bmp", O_TRUNC | O_CREAT | O_RDWR, 0666);
	write(bmp->fd, bmp->bmpfileheader, 14);
	write(bmp->fd, bmp->bmpinfoheader, 40);
	bmp->i = 0;
	while (bmp->i < gd->cnv.h)
	{
		write(bmp->fd, bmp->img + (gd->cnv.w
				* (gd->cnv.h - bmp->i - 1) * 3), 3 * gd->cnv.w);
		write(bmp->fd, bmp->bmppad, (4 - (gd->cnv.w * 3) % 4) % 4);
		bmp->i++;
	}
	free(bmp->img);
	free(bmp->bmpfileheader);
	free(bmp->bmpinfoheader);
	free(bmp->bmppad);
	close(bmp->fd);
}

void	ft_save_img(t_data *gd, int *img)
{
	t_bmp	this;

	this.filesize = 54 + 3 * gd->cnv.w * gd->cnv.h;
	this.img = (unsigned char *)malloc(3 * gd->cnv.w * gd->cnv.h);
	this.i = 0;
	while (this.i < gd->cnv.w)
	{
		this.j = 0;
		while (this.j < gd->cnv.h)
		{
			this.y = (gd->cnv.h - 1) - this.j;
			this.img[(this.i + this.y * gd->cnv.w)*3 + 2] = (unsigned char)
				(img[this.i + this.y * gd->cnv.w] >> 16);
			this.img[(this.i + this.y * gd->cnv.w)*3 + 1] = (unsigned char)
				((img[this.i + this.y * gd->cnv.w] << 16) >> 24);
			this.img[(this.i + this.y * gd->cnv.w)*3] = (unsigned char)
				((img[this.i + this.y * gd->cnv.w] << 24) >> 24);
			this.j++;
		}
		this.i++;
	}
	bmp_info(&this, gd);
	fill_bmp(&this, gd);
}
