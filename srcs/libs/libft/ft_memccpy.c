/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 20:47:29 by omercade          #+#    #+#             */
/*   Updated: 2020/01/13 18:43:41 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	unsigned char		value;

	value = c;
	dest = dst;
	i = 0;
	while (i < n)
	{
		dest[i] = *((unsigned char *)src + i);
		if (dest[i] == value)
		{
			return (&dest[i + 1]);
		}
		i++;
	}
	return (NULL);
}
