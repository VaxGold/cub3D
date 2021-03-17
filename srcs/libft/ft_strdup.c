/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 12:24:14 by omercade          #+#    #+#             */
/*   Updated: 2020/01/13 18:55:30 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;

	len = ft_strlen((char *)s1);
	if ((ptr = (char *)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_memcpy(ptr, (char *)s1, len);
	ptr[len] = '\0';
	return (ptr);
}
