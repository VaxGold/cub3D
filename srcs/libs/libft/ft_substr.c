/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:32:00 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:35:13 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen((char *)s) == 0)
		return (ft_strdup(""));
	if (ft_strlen((char *)s) < (size_t)start)
		return (ft_strdup(""));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[i] != 0)
	{
		*(str + i) = *((char *)s + start + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
