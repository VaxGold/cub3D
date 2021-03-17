/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:54:11 by omercade          #+#    #+#             */
/*   Updated: 2020/01/07 19:05:47 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *b, size_t len)
{
	unsigned int	i;
	unsigned char	*memory;

	memory = b;
	i = 0;
	while (i < len)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}
