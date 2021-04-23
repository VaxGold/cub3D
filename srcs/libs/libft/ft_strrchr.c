/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:25:49 by omercade          #+#    #+#             */
/*   Updated: 2020/01/13 14:48:29 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	value;
	char			*result;

	value = c;
	i = 0;
	result = 0;
	while (i <= ft_strlen((char *)s))
	{
		if (s[i] == value)
		{
			result = (char *)s + i;
		}
		i++;
	}
	return (result);
}
