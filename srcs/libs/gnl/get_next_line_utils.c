/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:54:27 by omercade          #+#    #+#             */
/*   Updated: 2021/04/15 21:41:50 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	a;
	unsigned int	l;
	char			*t;
	char			*str1;

	a = 0;
	l = (unsigned int)ft_strlen((char *)s1);
	t = (char *)malloc(l * sizeof(char) + 1);
	if (!t)
		return (NULL);
	str1 = (char *)t;
	while (a < l)
	{
		str1[a] = s1[a];
		a++;
	}
	str1[a] = '\0';
	return (t);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	ft_strtab(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
