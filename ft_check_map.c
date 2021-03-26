/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:00 by omercade          #+#    #+#             */
/*   Updated: 2021/03/26 21:43:40 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*int     test_map()
{
    
}*/

static void    save_map(t_data *gd, t_check *this)
{
    t_list  *map_line;
    int     i;

    map_line = this->first;
    gd->map_h = ft_lstsize(this->first);
    gd->map_w = 0;
    gd->map = malloc(sizeof(int *) * gd->map_h + 1);
    i = 0;
    while (map_line->next != NULL)
    {
        gd->map[i] = ft_strdup((const char *)map_line->content);
        if(ft_strlen((const char *)gd->map[i]) > (size_t)gd->map_w)
            gd->map_w = ft_strlen((const char *)gd->map[i]);
        map_line = map_line->next;
        i++;
    }
    gd->map[i] = "\0";
}

int     ft_check_map(t_data *gd, t_check *this)
{
    int     i;
    int     j;

    save_map(gd, this);
    i = 0;
    while(i < gd->map_h)
    {
        j = 0;
        while (j < gd->map_w)
        {
            j++;
        }
        i++;
    }
    //test_map();
    return(0);
}
