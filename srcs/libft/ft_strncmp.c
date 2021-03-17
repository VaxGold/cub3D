/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 11:57:25 by omercade          #+#    #+#             */
/*   Updated: 2020/01/20 20:52:52 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	int				diff;

	i = 0;
	diff = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
		{
			diff = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (diff);
		}
		i++;
	}
	if ((s1[i] == 0 || s2[i] == 0) && i != n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	}
	return (diff);
}
