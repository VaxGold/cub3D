/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flgcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:51 by omercade          #+#    #+#             */
/*   Updated: 2021/04/12 20:07:22 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_flgcmp(t_check *this, char c)
{
	char	str[2];
	char	*aux;

	str[0] = c;
	str[1] = '\0';
	if (ft_strchr(this->flag, c))
		return (ft_error(ft_strjoin(str, " Flag")));
	else
	{
		aux = this->flag;
		this->flag = ft_strjoin(aux, str);
		free(aux);
		return (0);
	}
}
