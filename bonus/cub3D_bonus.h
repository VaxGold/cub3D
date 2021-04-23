/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:39:18 by omercade          #+#    #+#             */
/*   Updated: 2021/04/21 18:34:14 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>

# include "../srcs/libs/gnl/get_next_line.h"
# include "../srcs/libs/libft/libft.h"

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
# define KEY_L_SHFT				257

# define MOVSPEED				0.1
# define ROTSPEED				0.075
# define JMPSPEED				0.5
# define JMPHGHT				4.0
# define GRAVITY				-0.98

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

typedef struct s_sprite
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bits;
	int		line;
	int		endian;
	int		uDiv;
	int		vDiv;
	double	uMove;
}				t_sprite;

typedef struct s_ss
{
	int		x;
	int		y;
	char	id;
}				t_ss;

typedef struct s_skybox
{
	t_texture		pX;
	t_texture		nX;
	t_texture		pY;
	t_texture		nY;
	t_texture		pZ;
	t_texture		nZ;
}				t_skybox;

typedef struct s_vector2
{
	int		x;
	int		y;
}				t_vector2;

typedef struct s_vector3
{
	int		x;
	int		y;
	int		z;
}				t_vector3;

typedef struct s_controls
{
	double	x;
	double	y;
	double	z;
	double	rot;
	int		ground;
	int		spdMod;
}				t_controls;

typedef struct s_actor
{
	double	posX;
	double	posY;
	double	posZ;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	mvSpd;
	double	rotSpd;
	double	jmpSpd;
}				t_actor;

typedef struct s_canvas
{
	t_img	img;
	void	*win;
	int		w;
	int		h;
}					t_canvas;

typedef struct s_map
{
	char		**this;
	int			w;
	int			h;
	int			nSprites;
	t_sprite	*ss;
	t_sprite	*objs;
	t_texture	fTex;
	t_texture	wTex;
	t_skybox	sBox;
}					t_map;

typedef struct s_data
{
	void		*mlx;
	int			state;		//0: main_menu, 1: level_completed, 2: game_over, 3: end_game, 4: game
	t_canvas	cnv;
	t_actor		ply;
	t_controls	axis;
	t_map		map;
	char		*map_selector[3];
	int			world;
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

int			map_reader(t_data *gd);
int			save_map(t_data *gd, t_list *first);
t_skybox	skybox_save(t_data *gd, char *line);
t_texture	texture_save(t_data *gd, char *line);

#endif

