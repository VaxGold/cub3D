/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:14:16 by omercade          #+#    #+#             */
/*   Updated: 2021/04/05 21:54:19 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    save_map(t_data *gd, t_check *this, char *line)
{
    int len;

    len = ft_strlen(line);
    if (this->init_m == 0)
    {
        this->first = ft_lstnew(ft_strdup(line));
        this->init_m = 1;
        gd->map_w = len;
    }
    else
    {
        ft_lstadd_back(&this->first, ft_lstnew(ft_strdup(line)));
        if (len > gd->map_w)
            gd->map_w = len;
    }
}

int     verify_map(t_data *gd, t_check *this)
{
    if(strlen(this->flag) == 8)
        return(ft_check_map(gd, this));
    else
        return(error_display("MAP FLAG"));
}

int     line_check(t_data *gd, t_check *this, char *line)
{
    int     i;

    i = space_skip(line, 0);
    if(!(line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '\n') && this->init_m == 1 && this->init_m--)
        return(verify_map(gd, this));
    if (line[i] == 'R')
        return(ft_check_res(gd, this, line));
    else if(line[i] == 'N' || line[i] == 'W' || line[i] == 'E' || line[i] == 'S')
        return(ft_check_tex(gd, this, line));
    else if(line[i] == 'F' || line[i] == 'C')
        return(ft_check_color(gd, this, line));
    else if(line[i] == '0' || line[i] == '1' || line[i] == '2')
        save_map(gd, this, line);
    else if(!(!line[i] && this->init_m == 0))       //NOT RELIABLE!?
        return(error_display("LINE READING"));
    return(0);
}

int    ft_reader(t_data *gd, char *rut)
{
    int		fd;
    int     ret;
	char 	*line;
    t_check this;

	fd = open(rut, O_RDONLY);
    this.flag = ft_strdup("");
    this.init_m = 0;
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (line_check(gd, &this, line) == -1)
        {
            ret = -1;
            free(line);
            line = NULL;
            break;
        }
		free(line);
        line = NULL;
        if (ret == 0)
            break;
	}
    close(fd);
    if(ret == 0 && this.init_m == 1)
        ret = verify_map(gd, &this);
    if (ret == -1 || strlen(this.flag) != 9)
        return(error_display("FILE READING"));
    return(0);
}