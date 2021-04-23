/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:05:23 by omercade          #+#    #+#             */
/*   Updated: 2020/01/22 12:42:49 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	f;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	f = 0;
	while (ft_strchr(set, s1[i]) != 0 && s1[i] != 0)
		i++;
	if (ft_strlen(s1) == i)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[ft_strlen(s1) - f]) && (ft_strlen(s1) - f) > 0)
		f++;
	return (ft_substr(s1, i, ft_strlen(s1) - (i + f) + 1));
}
