/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:11:29 by omercade          #+#    #+#             */
/*   Updated: 2021/03/11 20:31:19 by omercade         ###   ########.fr       */
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

typedef struct	s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	mvFb;
	double	mvSide;
	double	mvRot;
	double	rotSpd;
	double	mvSpd;
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
	int     scrW;
	int     scrH;
	t_img	img;
	int		**map;
}				t_game;

typedef struct	s_ray
{
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
	double	sideDistX;
	double	sideDistY;
	double deltaDistX;
	double deltaDistY;
	double	stepX;
	double	stepY;
	int		hit;
	int		side;
}				t_ray;

typedef struct		s_data
{
	t_game		game;
	t_player	player;
	t_ray		ray;
}					t_data;


#endif