/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:41:29 by omercade          #+#    #+#             */
/*   Updated: 2021/03/26 21:27:42 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     space_skip(char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	return(i);
}

int    check_flag(t_check *this, char c)
{
    int i;

    i = 0;
    if(ft_strchr(this->flag, c))
        return(1);
    else
    {
        while (this->flag[i] != '\0')
            i++;
        this->flag[i++] = c;
        this->flag[i] = '\0';
        return(0);
    }
}

int     check_all_flag(t_check this)
{
    if (!ft_strchr(this.flag, 'R'))
        return(1);
    else if (!ft_strchr(this.flag, 'N'))
        return(1);
    else if (!ft_strchr(this.flag, 'W'))
        return(1);
    else if (!ft_strchr(this.flag, 'E'))
        return(1);
    else if (!ft_strchr(this.flag, 'S'))
        return(1);
    else if (!ft_strchr(this.flag, 'O'))
        return(1);
    else if (!ft_strchr(this.flag, 'C'))
        return(1);
    else if (!ft_strchr(this.flag, 'F'))
        return(1);
    else if (!ft_strchr(this.flag, 'M'))
        return(1);
    return (0);
}