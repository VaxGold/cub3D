/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_res.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:20:30 by omercade          #+#    #+#             */
/*   Updated: 2021/04/01 19:25:45 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     get_resolution(char *line, int *i, int max_num)
{
	unsigned int	num;

	num = 0;
	if(!ft_isdigit(line[*i]))
		return(error_display("INVALID RESOLUTION"));
	while(ft_isdigit((line[*i])))
	{
		num = num * 10 + (line[*i] - 48);
		if (num > (unsigned int)max_num)
			num = max_num;
		(*i)++;
	}
	return((int)num);
}

int     ft_check_res(t_data *gd, t_check *this, char *line)
{
	int		i;

	i = space_skip(line, 0);
	if (line[i++] == 'R' && ft_isspace(line[i]))
	{
		i = space_skip(line, i);
		gd->cnv.w = get_resolution(line, &i, MAX_RES_W);
		if(gd->cnv.w == -1)
			return(error_display("WIDTH RESOLUTION"));
		i = space_skip(line, i);
		gd->cnv.h = get_resolution(line, &i, MAX_RES_H);
		if(gd->cnv.h == -1)
			return(error_display("HEIGHT RESOLUTION"));
		i = space_skip(line, i);
        if (line[i] != '\0')
            return(error_display("TOO MANY RESOLUTION ARGUMENTS"));
	}
	else
		return(error_display("RESOLUTION SET"));
	return(check_flag(this, 'R'));
}