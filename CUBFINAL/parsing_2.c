/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:17:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/27 17:30:09 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_rgb(t_data *data)
{
	if (data->rgb[0][0] == 'F' && data->rgb[0][1] == ' ')
	{
		if (!check_col_rgb(data, 0))
			return (0);
		if (data->rgb[1][0] == 'C' && data->rgb[1][1] == ' ')
		{
			if (!check_col_rgb(data, 1))
				return (0);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	parse_dir(t_data *data)
{
	if (data->dir[0][0] == 'N' && data->dir[0][1] == 'O'
		&& data->dir[0][2] == ' ')
	{
		if (data->dir[1][0] == 'S' && data->dir[1][1] == 'O'
			&& data->dir[1][2] == ' ')
		{
			if (data->dir[2][0] == 'W' && data->dir[2][1] == 'E'
				&& data->dir[2][2] == ' ')
			{
				if (data->dir[3][0] == 'E' && data->dir[3][1] == 'A'
					&& data->dir[3][2] == ' ')
					return (1);
				return (0);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	else
		return (0);
}

int	check_num(t_data *data)
{
	if (((data->ceiling[0] >= 0 && data->ceiling[0] <= 255)
			&& (data->ceiling[1] >= 0 && data->ceiling[1] <= 255)
			&& (data->ceiling[2] >= 0 && data->ceiling[2] <= 255))
		&& ((data->floor[0] >= 0 && data->floor[0] <= 255)
			&& (data->floor[1] >= 0 && data->floor[1] <= 255)
			&& (data->floor[2] >= 0 && data->floor[2] <= 255)))
		return (1);
	return (0);
}

void	get_rgb_v2(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->rgb_2 = malloc(sizeof(char *) * (data->len + 1));
	if (data->cubfile[i])
	{
		while (i < 2)
		{
			data->rgb_2[j++] = ft_substr(data->cubfile[i], 0, \
				ft_strlen(data->cubfile[i]));
			i++;
		}
	}
	data->rgb_2[j] = NULL;
}

int	parse_rgb_v2(t_data *data)
{
	if (data->rgb_2[0][0] == 'F' && data->rgb_2[0][1] == ' ')
	{
		if (!check_col_rgb_v2(data, 0))
			return (0);
		if (data->rgb_2[1][0] == 'C' && data->rgb_2[1][1] == ' ')
		{
			if (!check_col_rgb_v2(data, 1))
				return (0);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
