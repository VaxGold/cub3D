/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:09:05 by omercade          #+#    #+#             */
/*   Updated: 2021/04/14 17:55:52 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_extension(char *arg, char *ext)
{
	int		max;
	int		min;
	int		i;

	max = (int)ft_strlen(arg);
	if ((int)ft_strlen(ext) > max)
		return (ft_error("Wrong file extension"));
	min = max - (int)ft_strlen(ext);
	i = 0;
	while ((min + i) < max)
	{
		if (arg[min + i] != ext[i])
			return (ft_error("Wrong file extension"));
		i++;
	}
	return (0);
}
