/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:30:39 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/14 17:31:06 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	isconfig(char *str)
{
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "WE", 2)
		|| !ft_strncmp(str, "EA", 2)
		|| !ft_strncmp(str, "F", 1)
		|| !ft_strncmp(str, "C", 1))
		return (1);
	return (0);
}

int	getmap(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	data->map = malloc(sizeof(char *) * (data->len + 1));
	if (!data->map)
		return (0);
	while (data->cubfile[i])
	{
		if (isconfig(data->cubfile[i]) == 1)
			j++;
		i++;
		if (j == 6)
			break ;
	}
	while (data->cubfile[i])
	{
		data->map[k++] = ft_strdup(data->cubfile[i++]);
	}
	data->map[k] = NULL;
	data->k = k;
	return (1);
}

int	longestline(t_data *data)
{
	int		i;
	size_t	len;

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

int	isvalid(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int	isplayer(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}
