/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:09 by omercade          #+#    #+#             */
/*   Updated: 2021/04/01 19:28:29 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     set_texture(t_data *gd, char *r, char c)
{
	int txpos;

	if(c == 'N')
		txpos = 0;
	else if(c == 'E')
		txpos = 1;
	else if(c == 'W')
		txpos = 2;
	else if(c == 'O')
		txpos = 3;
	else if(c == 'S')
		txpos = 4;
	else
		return(error_display("INVALID TEXTURE FLAG"));
	gd->tex[txpos].img = mlx_xpm_file_to_image(gd->mlx, r, &gd->tex[txpos].width, &gd->tex[txpos].height);
	if (!gd->tex[txpos].img)
		return(error_display("INVALID TEXTURE ROUTE"));
	gd->tex[txpos].addr = (int *)mlx_get_data_addr(gd->tex[txpos].img, &gd->tex[txpos].bits, &gd->tex[txpos].line, &gd->tex[txpos].endian);
	return(0);
}

int     get_texture(t_data *gd, char *line, int i, char c)
{
	char			*r;
	unsigned int	init;
	int				len;

	init = (unsigned int)i;
	len = 0;
	while (!ft_isspace(line[i + len]) && line[i + len] != '\0')
		len++;
	r = ft_substr(line, init, (size_t)len);
	if(set_texture(gd, r, c))
		return(-1);
	return(i + len);
}

int     ft_check_tex(t_data *gd, t_check *this, char *line)
{
	int     i;
	int		mod;
	char    c;

	i = space_skip(line, 0);
	mod = 2;
	if (line[i] == 'N' && line[i + 1] == 'O')
		c = 'N';
	else if (line[i] == 'E' && line[i + 1] == 'A')
		c = 'E';
	else if (line[i] == 'W' && line[i + 1] == 'E')
		c = 'W';
	else if (line[i] == 'S' && line[i + 1] == 'O')
		c = 'O';
	else if (line[i] == 'S' && line[i + 1] == ' ' && mod--)
		c = 'S';
	else
		return(error_display("INVALID TEXTURE"));
	if(check_flag(this, c))
		return(-1);
	if (ft_isspace(line[i + mod]))
		i = space_skip(line, i + mod);
	i = get_texture(gd, line, i, c);
	if (i == -1)
		return(-1);
	i = space_skip(line, i);
	if (line[i] != '\0')
		return(error_display("TOO MANY TEXTURE ARGUMENTS"));
	return(0);
}
