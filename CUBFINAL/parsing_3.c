/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:58:52 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/27 17:30:28 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_dir(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->dir = malloc(sizeof(char *) * (data->len + 1));
	if (data->cubfile[i])
	{
		while (i < 4)
		{
			data->dir[j++] = ft_substr(data->cubfile[i], 0, \
				ft_strlen(data->cubfile[i]));
			i++;
		}
	}
	data->dir[j] = NULL;
}

int	check_rgb(t_data *data)
{
	int	i;

	i = 4;
	if (data->cubfile[0])
	{
		while (data->cubfile[i])
		{
			if (data->cubfile[i][0] == '\0')
				i++;
			else
				break ;
		}
	}
	return (i);
}

void	get_rgb(t_data *data)
{
	int	i;
	int	j;

	i = check_rgb(data);
	j = 0;
	data->rgb = malloc(sizeof(char *) * (data->len + 1));
	if (data->cubfile[0])
	{
		data->rgb[j++] = ft_substr(data->cubfile[i], 0, \
			ft_strlen(data->cubfile[i]));
		i++;
		data->rgb[j++] = ft_substr(data->cubfile[i], 0, \
			ft_strlen(data->cubfile[i]));
	}
	data->rgb[j] = NULL;
}

int	check_col_rgb(t_data *data, int j)
{
	int	i;
	int	flag;
	int	flag2;

	i = 1;
	flag = 0;
	flag2 = 0;
	while (data->rgb[j][i] == ' ')
		i++;
	if (data->rgb[j][i] == '\0')
		return (0);
	while (data->rgb[j][i])
	{
		if (ft_isdigit(data->rgb[j][i]))
		{
			i++;
			if (flag)
				flag = 0;
		}
		else if (data->rgb[j][i] == ',' && !flag)
		{
			flag2++;
			flag = 1;
			i++;
		}
		else
			return (0);
	}
	if (flag2 != 2)
		return (0);
	return (1);
}

int	check_col_rgb_v2(t_data *data, int j)
{
	int	i;
	int	flag;
	int	flag2;

	i = 1;
	flag = 0;
	flag2 = 0;
	while (data->rgb_2[j][i] == ' ')
		i++;
	if (data->rgb_2[j][i] == '\0')
		return (0);
	while (data->rgb_2[j][i])
	{
		if (ft_isdigit(data->rgb_2[j][i]))
		{
			i++;
			if (flag)
				flag = 0;
		}
		else if (data->rgb_2[j][i] == ',' && !flag)
		{
			flag2++;
			flag = 1;
			i++;
		}
		else
			return (0);
	}
	if (flag2 != 2)
		return (0);
	return (1);
}
