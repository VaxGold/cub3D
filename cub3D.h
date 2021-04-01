/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:11:29 by omercade          #+#    #+#             */
/*   Updated: 2021/04/01 21:17:14 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
#include <fcntl.h>

# include "srcs/mlx/mlx.h"
# include "srcs/gnl/get_next_line.h"
# include "srcs/libft/libft.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_A_LEFT	    		123
# define KEY_A_RIGHT			124
# define KEY_TAB				48
# define KEY_L_SHFT				257

# define TEX_W					100
# define TEX_H					100
# define MOVSPEED               0.1
# define ROTSPEED               0.075

# define MAX_RES_W               4096
# define MAX_RES_H               2160


typedef struct	s_check
{
	int			init_m;
	char		*flag; 
	t_list		*first;
}				t_check;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct		s_texture
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bits;
	int		line;
	int		endian;
}					t_texture;

typedef struct	s_controls
{
	double	x;
	double	y;
	double	rot;
	int		spdMod;					//para sprint
}				t_controls;

typedef struct	s_actor
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

typedef struct		s_canvas
{
	t_img	img;
	void    *win;
	int		w;
	int		h;
}					t_canvas;


typedef struct		s_data
{
	void		*mlx;
	t_canvas	cnv;
	t_actor		actor;
	t_controls	axis;
	t_texture	tex[5];				//La posicion [4] es para el sprite
	int			color[2];			//color[0] = techo, color[1] = suelo
	char		**map;
	int			map_w;
	int			map_h;
}					t_data;

typedef struct	s_raycast
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
	double	perpWallDist;
	int		lineHeight;
}				t_raycast;

typedef struct		s_render
{
	int		drawStart;
	int		drawEnd;
	int		texNum;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
}					t_render;

int		ft_error(char *str);

int     close_window(t_data *gd);
int     key_press(int key_code, t_data *gd);
int     key_release(int key_code, t_data *gd);
void    key_events(t_data *gd);

void    ft_yaw(t_data *gd, double spd);
void    ft_displacement(t_data *gd, double spd);
void    ft_transform(t_data *gd);

int    ft_reader(t_data *gd, char *rut);

int     ft_check_map(t_data *gd, t_check *this);
int     ft_check_tex(t_data *gd, t_check *this, char *line);
int     ft_check_color(t_data *gd, t_check *this, char *line);
int     ft_check_res(t_data *gd, t_check *this, char *line);

int		error_display(char *str);
int   	check_flag(t_check *this, char c);
int     space_skip(char *line, int i);

#endif