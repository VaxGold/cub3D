/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:11:29 by omercade          #+#    #+#             */
/*   Updated: 2021/03/18 20:54:16 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

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
# define KEY_Q	    			12
# define KEY_E					14
# define KEY_A_LEFT	    		123
# define KEY_A_RIGHT			124
# define KEY_TAB				48
# define KEY_L_SHFT				257

# define COLS					24
# define ROWS					24
# define TILE_SIZE				50
# define MOVSPEED               0.1
# define ROTSPEED               0.075

typedef struct	s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	mvSpd;
	double	rotSpd;
}				t_player;

typedef struct	s_controls
{
	double	x;
	double	y;
	double	rot;
	int		run;
}				t_controls;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_game
{
	void    *mlx;
	void    *win;
	int     scrW;
	int     scrH;
	t_img	img;
	int		**map;
}				t_game;

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

typedef struct		s_textures
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bits;
	int		line;
	int		endian;
}					t_textures;

typedef struct		s_data
{
	t_game		game;
	t_player	actor;
	t_controls	axis;
	t_textures	txtr;
	int			txtW;
	int			txtH;
}					t_data;

void    ft_yaw(t_data *gd, double spd);
void    ft_displacement(t_data *gd, double spd);
void    ft_transform(t_data *gd);

int     close_game(t_data *gd);
int     key_press(int key_code, t_data *gd);
int     key_release(int key_code, t_data *gd);
void    key_events(t_data *gd);

#endif