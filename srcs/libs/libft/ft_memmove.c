/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:16:25 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:26:56 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	if (((unsigned char *)dst == 0 && (unsigned char *)src == 0)
		|| (dst == src))
		return (NULL);
	temp = (unsigned char *)dst;
	if ((unsigned char *)src < temp)
	{
		while (len > 0)
		{
			len--;
			temp[len] = *((unsigned char *)src + len);
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			temp[i] = *((unsigned char *)src + i);
			i++;
		}
	}
	return (dst);
}
