/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:21 by omercade          #+#    #+#             */
/*   Updated: 2021/03/26 20:55:18 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int     get_ncolor(char *line, int *i)
{
    int num;

    num = 0;
    if(!ft_isdigit(line[*i]))
        return(-1);
    while(ft_isdigit(line[*i]))
        num = num * 10 + (line[*i++] - 48);
    return(num);
}

int     get_rgb(t_data *gd, char *line, int *i, int pos)
{
    int r;
    int g;
    int b;

    r = get_ncolor(line, i);
    *i = space_skip(line, *i);
    if(line[*i] != ',')
        return(1);
    *i = space_skip(line, *i);
    g = get_ncolor(line, i);
    *i = space_skip(line, *i);
    if(line[*i] != ',')
        return(1);
    *i = space_skip(line, *i);
    b = get_ncolor(line, i);
    if(r == -1 || g == -1 || b == -1)
        return(1);
    gd->color[pos] = create_rgb(r, g, b);
    return(0);
}

int     ft_check_color(t_data *gd, t_check *this, char *line)
{
    int i;

    i = 0;
    i = space_skip(line, i);
    if (line[i] == 'S')
    {
        i = space_skip(line, i);
    }
    else
        return(1);
    if (get_rgb(gd, line, &i, 0))
        return(1);
    i = space_skip(line, i);
    if (get_rgb(gd, line, &i, 1))
        return(1);
    i = space_skip(line, i);
    if (line[i] != '\0')
        return(1);
    return(check_flag(this, 'S'));
}
