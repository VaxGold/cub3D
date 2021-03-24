/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:09 by omercade          #+#    #+#             */
/*   Updated: 2021/03/24 21:28:17 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     ft_check_tex(t_data *gd, t_check *this, char *line)
{
    int i;

    i = 0;
    i = space_skip(line, i);
    if(line[i] == "N")
        get_north_tex();
    else if(line[i] == "W")
        get_west_tex();
    else if(line[i] == "E")
        get_east_tex();
    else if(line[i] == "S")
    {
        if (line[i + 1] == "O")
            get_south_tex();
        else if(line[i + 1] == " ")
            get_sprite();
        else
            return(1);
    }
    if(i == -1)
        return(1);
    i = space_skip(line, i);
    if(line[i] != "\0")
        return (1); 
    return(0);
}
