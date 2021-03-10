/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:11:29 by omercade          #+#    #+#             */
/*   Updated: 2021/03/09 20:43:45 by omercade         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

typedef struct	s_move
{
	double	fb;
	double	rl;
	double	rot;
}				t_move;

typedef struct	s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	t_move	move;
}				t_player;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_game
{
	void    *mlx;
	void    *win;
	int     screen_w;
	int     screen_h;
	t_img	img;
	int		**map;
	double	time;
	double	oldTime;
}				t_game;

typedef struct	s_tiles
{
	int		width;
	int		heigth;
	t_img	img;
}				t_tiles;

/*typedef struct	s_raycast
{
	
}				t_raycast;*/

typedef struct		s_all
{
	t_game game;
	t_player player;
}					t_all;


#endif