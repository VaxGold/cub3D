/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:11:29 by omercade          #+#    #+#             */
/*   Updated: 2021/04/20 18:25:40 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>

# include "srcs/libs/gnl/get_next_line.h"
# include "srcs/libs/libft/libft.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_A_LEFT				123
# define KEY_A_RIGHT			124
# define KEY_TAB				48
# define KEY_L_SHFT				257

# define MOVSPEED				0.1
# define ROTSPEED				0.075

# define MAX_RES_W				2560
# define MAX_RES_H				1440
# define MIN_RES_W				100
# define MIN_RES_H				100

# define UDIV					1
# define VDIV					1
# define UMOVE					0.0

typedef struct s_check
{
	int			init_m;
	char		*flag;
	t_list		*first;
}				t_check;

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bits;
	int		line;
	int		endian;
}				t_texture;

typedef struct s_sprites
{
	int		x;
	int		y;
}				t_sprites;

typedef struct s_controls
{
	double	x;
	double	y;
	double	rot;
	int		spdMod;
}				t_controls;

typedef struct s_actor
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	mvSpd;
	double	rotSpd;
}				t_actor;

typedef struct s_canvas
{
	t_img	img;
	void	*win;
	int		w;
	int		h;
}					t_canvas;

typedef struct s_data
{
	void		*mlx;
	t_canvas	cnv;
	t_actor		actor;
	t_controls	axis;
	t_texture	tex[5];
	int			color[2];
	int			nSprites;
	t_sprites	*spr;
	char		**map;
	int			map_w;
	int			map_h;
}					t_data;

typedef struct s_raycast
{
	double	dirX;
	double	dirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	stepX;
	double	stepY;
	int		hit;
	int		side;
	int		face;
	double	perpWallDist;
	int		lineHeight;
}				t_raycast;

typedef struct s_render
{
	int		drawStart;
	int		drawEnd;
	int		texNum;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
}					t_render;

typedef struct s_spritecast
{
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		vMoveScreen;
	int		spriteHeight;
	int		spriteWidth;
	int		drawStartY;
	int		drawEndY;
	int		drawStartX;
	int		drawEndX;
}				t_spritecast;

typedef struct s_bmp
{
	unsigned char	*img;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	unsigned char	*bmppad;
	int				filesize;
	int				y;
	int				i;
	int				j;
	int				fd;
}				t_bmp;

int			ft_error(char *str);
int			ft_spaceskip(char *line, int i);
int			ft_flgcmp(t_check *this, char c);
int			ft_extension(char *arg, char *ext);
char		**ft_matrixcpy(int rows, char **matrix);

void		free_2Dchar(char **ptr);
void		secure_free(void *ptr);

int			close_window(t_data *gd);
int			key_press(int key_code, t_data *gd);
int			key_release(int key_code, t_data *gd);

double		ft_raycast(t_data *gd, int x);
void		color_fill(t_data *gd, int end, t_sprites point, int color);
void		face_orientation(t_data *gd, t_raycast *ryc, int side);

void		ft_sprites(t_data *gd, double *zBuffer);
void		sortSprites(int *spriteOrder, double *spriteDist, int nSprites);
void		countSprites(t_data *gd);
void		desallocSprites(double *spriteDist,
				int *spriteOrder, double *zBuffer);

void		ft_transform(t_data *gd);

int			ft_parse(t_data *gd, char *rut);
int			checkMap(t_data *gd, t_check *this);
int			fill_map(t_data *gd, char *str, int n);
int			checkResolution(t_data *gd, t_check *this, char *line);
int			checkTexture(t_data *gd, t_check *this, char *line);
int			checkColor(t_data *gd, t_check *this, char *line);

void		ft_save_img(t_data *gd, int *img);

#endif
