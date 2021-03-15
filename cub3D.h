/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:11:29 by omercade          #+#    #+#             */
/*   Updated: 2021/03/15 20:37:04 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# include "mlx/mlx.h"
//# include "minilibx/mms/mlx.h"
//# include "minilibx/opengl/mlx.h"

//# include "libft"

# define TRUE					1
# define FALSE					0

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

# define COLS					24
# define ROWS					24
# define TILE_SIZE				50
# define MOVSPEED               0.2
# define ROTSPEED               0.1

typedef struct	s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_player;

typedef struct	s_controls
{
	double	x;
	double	y;
	double	rot;
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

typedef struct	s_ray
{
	double	dirX;
	double	dirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	stepX;
	double	stepY;
	int		hit;
	int		side;
}				t_ray;

typedef struct		s_data
{
	t_game		game;
	t_player	actor;
	t_controls	axis;
}					t_data;


#endif