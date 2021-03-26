/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:09 by omercade          #+#    #+#             */
/*   Updated: 2021/03/26 21:28:27 by omercade         ###   ########.fr       */
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
        return(1);
    gd->tex[txpos].img = mlx_xpm_file_to_image(gd->mlx, r, &gd->tex[txpos].width, &gd->tex[txpos].height);
    if (!gd->tex[txpos].img)
        return(1);
    gd->tex[txpos].addr = (int *)mlx_get_data_addr(gd->tex[txpos].img, &gd->tex[txpos].bits, &gd->tex[txpos].line, &gd->tex[txpos].endian);
    return(0);
}

int     get_texture(t_data *gd, char *line, int *i, char c)
{
    char    *r;
    char    *init;
    int     len;

    r = "\0";
    if(ft_isprint(line[*i]))
    {
        init = &line[*i];
        len = 0;
        while(!ft_isspace(line[*i++]))
            len++;
        ft_strlcpy(r, init, (size_t)len);
    }
    else
        return(1);
    if(set_texture(gd, r, c))
        return(1);
    return(0);
}

int     ft_check_tex(t_data *gd, t_check *this, char *line)
{
    int     i;
    char    c;

    i = 0;
    i = space_skip(line, i);
    if (line[i] == 'N' && line[i + 1] == 'O')
        c = 'N';
    else if (line[i] == 'E' && line[i + 1] == 'A')
        c = 'E';
    else if (line[i] == 'W' && line[i + 1] == 'E')
        c = 'W';
    else if (line[i] == 'S' && line[i + 1] == 'O')
        c = 'O';
    else if (line[i] == 'S' && line[i + 1] == ' ')
        c = 'S';
    else
        return(1);
    if(check_flag(this, c))
        return(1);
    i = space_skip(line, i + 2);
    if (get_texture(gd, line, &i, c))
        return(1);
    i = space_skip(line, i);
    if (line[i] != '\0')
        return(1);
    return(0);
}
