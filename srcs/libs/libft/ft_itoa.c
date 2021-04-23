/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:23:21 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:20:50 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ndigit(int n)
{
	int	res;

	if (n <= 9 && n >= -9)
		return (1);
	res = 1;
	while (!(n <= 9 && n >= -9))
	{
		n = n / 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int		dig;
	char	*str;

	dig = ft_ndigit(n);
	if (n < 0)
		dig++;
	str = malloc(dig + 1);
	if (!str)
		return (NULL);
	str[dig] = '\0';
	while (!(n <= 9 && n >= -9))
	{
		if (n < 0)
			str[--dig] = (n % 10) * -1 + '0';
		else
			str[--dig] = (n % 10) + '0';
		n = n / 10;
	}
	if (n < 0)
		str[--dig] = (n % 10) * -1 + '0';
	else
		str[--dig] = (n % 10) + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
