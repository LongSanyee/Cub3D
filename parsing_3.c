/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:58:52 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/21 00:51:10 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_rgb(t_data *data)
{
	int	i;
	int	j;

	i = check_rgb(data);
	j = 0;
	data->rgb = malloc(sizeof(char *) * (data->len + 1));
	if (!data->rgb)
		return ;
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

static int	check_rgb_chars(char *str, int i)
{
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
			flag = 0;
		}
		else if (str[i] == ',' && !flag)
		{
			flag2++;
			flag = 1;
			i++;
			while (str[i] && str[i++] == ' ')
				if (!ft_isdigit(str[i]))
					return (0);
		}
		else
			return (0);
	}
	return (flag2 == 2);
}

int	check_col_rgb(t_data *data, int j)
{
	int	i;

	i = 1;
	while (data->rgb[j][i] == ' ')
		i++;
	if (data->rgb[j][i] == '\0')
		return (0);
	return (check_rgb_chars(&data->rgb[j][i], 0));
}

static int	check_rgb_chars_v2(char *str, int i)
{
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
			flag = 0;
		}
		else if (str[i] == ',' && !flag)
		{
			flag2++;
			flag = 1;
			i++;
			while (str[i] && str[i++] == ' ')
				if (!ft_isdigit(str[i]))
					return (0);
		}
		else
			return (0);
	}
	return (flag2 == 2);
}

int	check_col_rgb_v2(t_data *data, int j)
{
	int	i;

	i = 1;
	while (data->rgb_2[j][i] == ' ')
		i++;
	if (data->rgb_2[j][i] == '\0')
		return (0);
	return (check_rgb_chars_v2(&data->rgb_2[j][i], i));
}
