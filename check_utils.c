/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:41:29 by omercade          #+#    #+#             */
/*   Updated: 2021/04/02 20:21:50 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int   error_display(char *str)
{
    printf("%s ERROR...\n", str);
    return(-1);
}

int     space_skip(char *line, int i)
{
	while ((line[i] == '\t' || line[i] == ' '))
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