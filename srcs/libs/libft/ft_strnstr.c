/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:43:31 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:34:12 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (ft_strlen((char *)needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] != 0)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strlen((char *)needle) <= (len - i))
			{
				if (ft_strncmp((char *)haystack + i,
						(char *)needle, ft_strlen((char *)needle)) == 0)
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
