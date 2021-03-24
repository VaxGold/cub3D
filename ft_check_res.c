/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_res.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:30 by omercade          #+#    #+#             */
/*   Updated: 2021/03/24 21:28:16 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     get_resolution(char *line, int *i, int max_res)
{
	unsigned int	num;

	if(!ft_isdigit(line[*i]))
		return(-1);
	while(ft_isdigit((line[*i])))
	{
		num = num * 10 + (line[*i] - 48);
		if (num > max_res)
		{
			while(ft_isdigit(line[*i++]))
				if(!ft_isdigit(line[*i]))
					return(-1);
			return(max_res);
		}
		*i++;
	}
	if(!ft_isdigit(line[*i]) && !ft_isspace(line[*i]))
		return(-1);
	return((int)num);
}

int     ft_check_res(t_data *gd, t_check *this, char *line)
{
	int		temp;
	int		i;

	i = 0;
	i = space_skip(line, i);
	if (line[i] == "R" && i++)
	{
		/*if(check_flag(this, 'R'))
			return(1);*/
		if(ft_isdigit(line[i]))
			return(1);
		i = space_skip(line, i);
		if(gd->cnv.w = get_resolution(line, &i, MAX_RES_W) == -1)
			return(1);
		if(ft_isdigit(line[i]))
			return(1);
		i = space_skip(line, i);
		if(gd->cnv.h = get_resolution(line, &i, MAX_RES_H) == -1)
			return(1);
		i = space_skip(line, i);
        if (line[i] != "\0")
            return(1);
	}
	else
		return(1);
	return(check_flag(this, 'R'));
}
