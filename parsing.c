/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:58:03 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/15 16:37:49 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validatepadding(t_data *data)
{
	t_vars	vars;

	vars.i = 0;
	vars.len = longestline(data);
	data->longestline = vars.len;
	while (data->map[vars.i])
	{
		if (vars.len > ft_strlen(data->map[vars.i]))
		{
			vars.tmp = data->map[vars.i];
			vars.updated = malloc(vars.len + 1);
			if (!vars.updated)
				return (0);
			vars.k = ft_strlen(data->map[vars.i]);
			ft_strlcpy(vars.updated, data->map[vars.i], vars.len + 1);
			while (vars.k < vars.len)
				vars.updated[vars.k++] = ' ';
			vars.updated[vars.k] = '\0';
			data->map[vars.i] = vars.updated;
			free(vars.tmp);
		}
		vars.i++;
	}
	return (1);
}

int	validatemap(t_data *data)
{
	int	i;
	int	j;
	int	flag;

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

int	validateinside(t_data *data)
{
	char	c;
	size_t	y;
	size_t	x;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			c = data->map[x][y];
			if (c == '0' || isplayer(c))
			{
				if ((x > 0 && data->map[x - 1][y] == ' ')
					|| (x < data->k - 1 && data->map[x + 1][y] == ' ')
					|| (y > 0 && data->map[x][y - 1] == ' ')
					|| (!data->map[x][y + 1] || data->map[x][y + 1] == ' '))
					return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}
