/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:50:38 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/28 11:53:18 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	old_result;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		old_result = result;
		result = result * 10 + str[i] - '0';
		if (old_result != result / 10)
			return (0);
		i++;
	}
	return (result * sign);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t		i;
	size_t		srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
	{
		return (srclen);
	}
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*q;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	if (start >= slen)
		return ((char *) ft_calloc(1, sizeof(char)));
	i = 0;
	q = (char *)malloc(sizeof(char) * (len + 1));
	if (!q)
		return (NULL);
	while (i < len)
	{
		q[i] = s[start + i];
		i++;
	}
	q[i] = '\0';
	return (q);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return ((unsigned char )s1[i] - (unsigned char )s2[i]);
	}
	return (0);
}

char    *ft_strtrim(char *s1, char *set)
{
    size_t  start;
    size_t  end;
    char    *str;
    if (!s1)
        return (NULL);
    if (!set)
        return (ft_strdup(s1));
    start = 0;
    end = ft_strlen(s1);
    while (s1[start] && ft_strchr(set, s1[start]))
            start++;
    while (end > start && ft_strchr(set, s1[end - 1]))
            end--;
    str = malloc(end - start + 1);
    if (!str)
        return (NULL);
    ft_strlcpy(str, s1 + start, end - start + 1);
    return (str);
}
