/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:14:16 by omercade          #+#    #+#             */
/*   Updated: 2021/03/22 21:31:35 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    save_map(t_check *this, char *line)
{
    if (this->init_m == 0)
    {
        this->first = ft_lstnew(line);
        this->init_m = 1;
    }
    else
        ft_lstadd_back(&this->first, ft_lstnew(line));
}


int     line_check(t_data *gd, t_check *this, char *line)
{
    int     control;
    int     i;

    control = 0;
    i = 0;
    while(ft_isspace(line[i]))
        i++;
    if(line[i] != "1" && this->init_m == 1 && this->init_m--)
        ft_check_map(gd, this, line);
    if (line[i] == "R")
        control = ft_check_res(gd, this, line);
    else if(line[i] == "N")
        control = ft_check_tex(gd, this, line);
    else if(line[i] == "S")
    {
        if (line[i + 1]  == "O")
           control = ft_check_tex(gd, this, line); 
        else if (line[i + 1] == " ")
            control = ft_check_spr(gd, this, line);
        else
            return(1);    
    }
    else if(line[i] == "W")
        control = ft_check_tex(gd, this, line);
    else if(line[i] == "E")
        control = ft_check_tex(gd, this, line);
    else if(line[i] == "F")
        control = ft_check_color(gd, this, line);
    else if(line[i] == "C")
        control = ft_check_color(gd, this, line);
    else if(line[i] == "1")
        save_map(this, line);
    else if(!(!line[i] && this->init_m == 0))
        control = -1;
    /*else if(!line[i] && this->init_m == 0)
        ;
    else
        control = 1;*/
    return(control);
}

int    ft_reader(t_data *gd, char *rut)
{
    int		fd;
    int     err;
	char 	*line;
    t_check this;

	fd = open(rut, O_RDONLY);
	while (err = get_next_line(fd, &line) == 1)
	{
		if (line_check(gd, &this, line) == 1)
            return(1);
		free(line);
	}
    if (err == -1)
        return(1);
    return(0);
}
