/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:59:50 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/27 17:30:50 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_dir_v2(t_data *data)
{
	int	i;

	i = 2;
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

void	get_dir_v2(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = check_dir_v2(data);
	j = 0;
	count = 0;
	data->dir_2 = malloc(sizeof(char *) * (data->len + 1));
	if (data->cubfile[0])
	{
		while (count < 4)
		{
			data->dir_2[j++] = ft_substr(data->cubfile[i], 0, \
				ft_strlen(data->cubfile[i]));
			i++;
			count++;
		}
	}
	data->dir_2[j] = NULL;
}

int	parse_dir_v2(t_data *data)
{
	if (data->dir_2[0][0] == 'N' && data->dir_2[0][1] == 'O'
		&& data->dir_2[0][2] == ' ')
	{
		if (data->dir_2[1][0] == 'S' && data->dir_2[1][1] == 'O'
			&& data->dir_2[1][2] == ' ')
		{
			if (data->dir_2[2][0] == 'W' && data->dir_2[2][1] == 'E'
				&& data->dir_2[2][2] == ' ')
			{
				if (data->dir_2[3][0] == 'E' && data->dir_2[3][1] == 'A'
					&& data->dir_2[3][2] == ' ')
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
