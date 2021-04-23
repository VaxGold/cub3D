/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:01:00 by omercade          #+#    #+#             */
/*   Updated: 2020/01/13 14:46:10 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	i = 0;
	ch = c;
	while (i <= ft_strlen((char *)s))
	{
		if (s[i] == ch)
			return (((char *)s + i));
		i++;
	}
	return (NULL);
}
