/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:41:29 by omercade          #+#    #+#             */
/*   Updated: 2021/04/06 20:37:43 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	face_orientation(t_data *gd, t_raycast *ryc, int side)
{
    ryc->side = side;
	if (gd->actor.posX > (double)ryc->mapX)
	{
		if (ryc->side == 1 && gd->actor.posY > ryc->mapY)
			ryc->face = 2;
		else if (ryc->side == 1 && gd->actor.posY  < ryc->mapY)
			ryc->face = 1;
		else
			ryc->face = 3;
	}
	else
	{
		if (ryc->side == 1 && gd->actor.posY > ryc->mapY)
			ryc->face = 2;
		else if (ryc->side == 1 && gd->actor.posY < ryc->mapY)
			ryc->face = 1;
		else
			ryc->face = 0;
	}
}

int   error_display(char *str)
{
    printf("Error\n%s\n", str);
    return(-1);
}

int     space_skip(char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	return(i);
}

int    check_flag(t_check *this, char c)
{
    char    str[2];
    char    *aux;

    if(ft_strchr(this->flag, c))
    {
        printf("%c ", c);
        return(error_display("FLAG"));
    }
    else
    {
        str[0] = c;
        str[1] = '\0';
        aux = this->flag;
        this->flag = ft_strjoin(aux, str);
        free(aux);
        return(0);
    }
}