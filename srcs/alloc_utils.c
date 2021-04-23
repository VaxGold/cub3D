/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:16:27 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:02:44 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_2Dchar(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != 0)
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	secure_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}
