/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkColor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:01:08 by omercade          #+#    #+#             */
/*   Updated: 2021/04/12 20:16:57 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_ncolor(char *line, int *i)
{
	int	num;
	int	ret;

	num = 0;
	ret = *i;
	if (!ft_isdigit(line[ret]))
		return (ft_error("Invalid color"));
	while (ft_isdigit(line[ret]))
	{
		num = num * 10 + (line[ret++] - 48);
		if (num > 255)
			return (ft_error("Color out of range (0-255)"));
	}
	*i = ret;
	return (num);
}

int	get_rgb(t_data *gd, char *line, int i, char flg)
{
	int	r;
	int	g;
	int	b;

	r = get_ncolor(line, &i);
	i = ft_spaceskip(line, i);
	if (line[i] != ',')
		return (-1);
	i = ft_spaceskip(line, i + 1);
	g = get_ncolor(line, &i);
	i = ft_spaceskip(line, i);
	if (line[i] != ',')
		return (-1);
	i = ft_spaceskip(line, i + 1);
	b = get_ncolor(line, &i);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	if (flg == 'C')
		gd->color[0] = create_rgb(r, g, b);
	else if (flg == 'F')
		gd->color[1] = create_rgb(r, g, b);
	return (i);
}

int	checkColor(t_data *gd, t_check *this, char *line)
{
	int		i;
	char	flg;

	i = ft_spaceskip(line, 0);
	if ((line[i] == 'C' || line[i] == 'F') && ft_isspace(line[i + 1]))
		flg = line[i++];
	else
		return (ft_error("Color flag"));
	i = ft_spaceskip(line, i);
	i = get_rgb(gd, line, i, flg);
	if (i == -1)
		return (ft_error("Color set"));
	i = ft_spaceskip(line, i);
	if (line[i] != '\0')
		return (ft_error("Too many color arguments"));
	return (ft_flgcmp(this, flg));
}
