/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:20:55 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 20:39:00 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**ft_matrixcpy(int rows, char **matrix)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = (char **)malloc((rows + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	while (i < rows)
	{
		cpy[i] = ft_strdup(matrix[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
