/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkTexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:00:57 by omercade          #+#    #+#             */
/*   Updated: 2021/04/21 17:56:15 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	set_texture(t_data *gd, char *r, char c)
{
	int	txpos;

	if (c == 'N')
		txpos = 0;
	else if (c == 'E')
		txpos = 2;
	else if (c == 'W')
		txpos = 1;
	else if (c == 'O')
		txpos = 3;
	else if (c == 'S')
		txpos = 4;
	else
		return (ft_error("Invalid texture flag"));
	gd->tex[txpos].img = mlx_xpm_file_to_image(gd->mlx, r,
			&gd->tex[txpos].width, &gd->tex[txpos].height);
	secure_free(r);
	if (!gd->tex[txpos].img)
		return (ft_error("Invalid texture route"));
	gd->tex[txpos].addr = (int *)mlx_get_data_addr(gd->tex[txpos].img,
			&gd->tex[txpos].bits, &gd->tex[txpos].line, &gd->tex[txpos].endian);
	return (0);
}

int	get_texture(t_data *gd, char *line, int i, char c)
{
	char			*r;
	unsigned int	init;
	int				len;

	init = (unsigned int)i;
	len = 0;
	while (!ft_isspace(line[i + len]) && line[i + len] != '\0')
		len++;
	r = ft_substr(line, init, (size_t)len);
	if (set_texture(gd, r, c))
		return (-1);
	return (i + len);
}

char	pick_texture(char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
		return ('N');
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return ('E');
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return ('W');
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return ('O');
	else if (line[i] == 'S' && line[i + 1] == ' ')
		return ('S');
	else
		return (0);
}

int	checkTexture(t_data *gd, t_check *this, char *line)
{
	int		i;
	int		mod;
	char	c;

	i = ft_spaceskip(line, 0);
	c = pick_texture(line, i);
	if (!c)
		return (ft_error("Texture argument"));
	else if (c == 'S')
		mod = 1;
	else
		mod = 2;
	if (ft_flgcmp(this, c))
		return (-1);
	if (ft_isspace(line[i + mod]))
		i = ft_spaceskip(line, i + mod);
	i = get_texture(gd, line, i, c);
	if (i == -1)
		return (-1);
	i = ft_spaceskip(line, i);
	if (line[i] != '\0')
		return (ft_error("Too many texture arguments"));
	return (0);
}
