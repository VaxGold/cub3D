/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:49:16 by omercade          #+#    #+#             */
/*   Updated: 2020/01/10 13:41:59 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long int	i;
	unsigned char		value;

	value = c;
	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == value)
		{
			return ((unsigned char *)s + i);
		}
		i++;
	}
	return (0);
}
