/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:15:36 by omercade          #+#    #+#             */
/*   Updated: 2020/01/08 11:43:00 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*memory;
	unsigned char	value;

	memory = b;
	value = c;
	i = 0;
	while (i < len)
	{
		memory[i] = value;
		i++;
	}
	return (memory);
}
