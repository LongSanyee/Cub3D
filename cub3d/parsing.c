/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:54:54 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/28 11:55:09 by rammisse         ###   ########.fr       */
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
	int k;

	i = 0;
	k = 0;
	data->map = malloc(sizeof(char *) * (data->len + 1));
	while (data->cubfile[i])
	{
		if (!isnotmap(data->cubfile[i]))
		{
			if (ft_strchr(data->cubfile[i], '1'))
			{
				data->map[k] = malloc(ft_strlen(data->cubfile[i]) + 1);
				ft_strlcpy(data->map[k], data->cubfile[i], ft_strlen(data->cubfile[i]) + 1);
				k++;
			}
		}
		i++;
	}
	data->map[k] = NULL;
	return (1);
}
