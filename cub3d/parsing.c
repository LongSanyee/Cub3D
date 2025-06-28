/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:54:54 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/28 19:37:32 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int getceiling(t_data *data)
{
	int	i;
	int k;
	int	result;
	int	j;

	i = 0;
	result = 0;
	k = 0;
	while (data->cubfile[i])
	{
		if (!ft_strncmp(data->cubfile[i], "C", 1))
		{
			j = 1;
			while (data->cubfile[i][j])
			{
				if (isnum(data->cubfile[i][j]))
					result = result * 10 + (data->cubfile[i][j] - '0');
				if (data->cubfile[i][j] == ',' || data->cubfile[i][j + 1] == '\0')
				{
					data->ceiling[k++] = result;
					result = 0;
				}
				j++;
			}
			break ;
		}
		i++;
	}
	return (1);
}

int getfloor(t_data *data)
{
	int	i;
	int k;
	int	result;
	int	j;

	i = 0;
	result = 0;
	k = 0;
	while (data->cubfile[i])
	{
		if (!ft_strncmp(data->cubfile[i], "F", 1))
		{
			j = 1;
			while (data->cubfile[i][j])
			{
				if (isnum(data->cubfile[i][j]))
					result = result * 10 + (data->cubfile[i][j] - '0');
				if (data->cubfile[i][j] == ',' || data->cubfile[i][j + 1] == '\0')
				{
					data->floor[k++] = result;
					result = 0;
				}
				j++;
			}
			break ;
		}
		i++;
	}
	return (1);
}

int isnotmap(char *str)
{
	if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3) ||
		!ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3) ||
		!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
		return (1);
	return (0);
}

int getmap(t_data *data)
{
	int i;
	int flag;
	int k;

	i = 0;
	k = 0;
	flag = 0;
	data->map = malloc(sizeof(char *) * (data->len + 1));
	if (!data->map)
		return (0);
	while (data->cubfile[i])
	{
		if (!isnotmap(data->cubfile[i]))
		{
			if (ft_strchr(data->cubfile[i], '1'))
			{
				flag = 1;
				data->map[k] = malloc(ft_strlen(data->cubfile[i]) + 1);
				ft_strlcpy(data->map[k], data->cubfile[i], ft_strlen(data->cubfile[i]) + 1);
				k++;
			}
			if (flag == 1 && !ft_strchr(data->cubfile[i], '1'))
				return (printf("Invalid MAP !\n"), exit(0), 0);
		}
		i++;
	}
	data->map[k] = NULL;
	data->k = k;
	return (1);
}

int longestline(t_data *data)
{
	int i;
	size_t len;

	i = 0;
	len = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) > len)
			len = ft_strlen(data->map[i]);
		i++;
	}
	return (len);
}

int validatepadding(t_data *data)
{
	int i;
	char *tmp;
	char *updated;
	size_t j;
	size_t	len;

	i = 0;
	len = longestline(data);
	while (data->map[i])
	{
		if (len > ft_strlen(data->map[i]))
		{
			tmp = data->map[i];
			updated = malloc(len + 1);
			if (!updated)
				return (0);
			j = ft_strlen(data->map[i]);
			ft_strlcpy(updated, data->map[i], len + 1);
			while (j < len)
				updated[j++] = ' ';
			updated[j] = '\0';
			data->map[i] = updated;
			free(tmp);
		}
		i++;
	}
	return (1);
}

int isvalid(char c)
{
	if (c == '0' || c == '1' || c == 'N' ||
		c == 'S' || c == 'E' || c == 'W' ||
			c == ' ')
			return (1);
	return (0);
}

int isplayer(char c)
{
	if (c == 'N' || c == 'S' ||
		c == 'E' || c == 'W')
			return (1);
	return (0);
}

int validatemap(t_data *data)
{
	int	i;
	int j;
	int flag;

	if (!validatepadding(data))
		return (-1);
	if (!validatewalls(data))
		return (0);
	i = 0;
	flag = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!isvalid(data->map[i][j]))
				return (0);
			if (isplayer(data->map[i][j]) && flag == 0)
				flag = 1;
			else if (isplayer(data->map[i][j]) && flag == 1)
				return (0);
			j++;
		}
		i++;
	}
	if (flag == 0)
		return (0);
	return (1);
}

int checkfirstlast(char *str)
{
	int		i;
	int		last;
	
	i = 0;
	last = ft_strlen(str) - 1;

	while (last >= 0 && str[last] == ' ')
		last--;
	if (last <= 0 || str[last] != '1')
		return (0);
	while (i < last)
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}
	
int validatewalls(t_data *data)
{
	size_t	i;
	int		last;
	
	i = 1;
	if (!checkfirstlast(data->map[0]) || !checkfirstlast(data->map[data->k - 1]))
		return (0);
	while (i < data->k)
	{
		last = ft_strlen(data->map[i]) - 1;
		while (last >= 0 && data->map[i][last] == ' ')
			last--;
		if (last <= 0)
			return (0);
		if (data->map[i][last] != '1' || data->map[i][0] != '1')
			return (0);
		i++;
	}
	return (1);
}

int validateinside(t_data *data)
{
	size_t y;
	size_t x;
	char	c;
	
	x = -1;
	while (data->map[++x])
	{
		if (x != 0 && x != data->k - 1)
		{
			y = -1;
			while (data->map[x][++y])
			{
				c = data->map[x][y];
				if (c == '0' || isplayer(c))
				{
					if (data->map[x - 1][y] == ' ' || data->map[x + 1][y] == ' ')
						return (0);
					if ((y > 0 && data->map[x][y - 1] == ' ') || data->map[x][y + 1] == ' ')
						return (0);
				}
			}
		}
	}
	return (1);
}
