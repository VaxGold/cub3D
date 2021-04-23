/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkResolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:00:43 by omercade          #+#    #+#             */
/*   Updated: 2021/04/12 20:39:32 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_resolution(char *line, int *i, int max_num)
{
	unsigned int	num;

	num = 0;
	if (!ft_isdigit(line[*i]))
		return (-1);
	while (ft_isdigit((line[*i])))
	{
		num = num * 10 + (line[*i] - 48);
		if (num > (unsigned int)max_num)
			num = max_num;
		(*i)++;
	}
	return ((int)num);
}

int	checkResolution(t_data *gd, t_check *this, char *line)
{
	int		i;

	i = ft_spaceskip(line, 0);
	if (line[i++] == 'R' && ft_isspace(line[i]))
	{
		i = ft_spaceskip(line, i);
		gd->cnv.w = get_resolution(line, &i, MAX_RES_W);
		if (gd->cnv.w == -1)
			return (ft_error("Width resolution"));
		i = ft_spaceskip(line, i);
		gd->cnv.h = get_resolution(line, &i, MAX_RES_H);
		if (gd->cnv.h == -1)
			return (ft_error("Height resolution"));
		i = ft_spaceskip(line, i);
		if (line[i] != '\0')
			return (ft_error("Too many arguments for resolution"));
	}
	else
		return (ft_error("Resolution set"));
	if (gd->cnv.w < MIN_RES_W)
		gd->cnv.w = MIN_RES_W;
	if (gd->cnv.h < MIN_RES_H)
		gd->cnv.h = MIN_RES_H;
	return (ft_flgcmp(this, 'R'));
}
