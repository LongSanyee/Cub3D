/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:34:34 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/04 10:36:20 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void trimtextures(t_data *data)
{
	int i;
	char *tmp;
	
	i = 0;
	while (i < 4)
	{
		tmp = data->textures[i];
		data->textures[i] = ft_strtrim(data->textures[i], " 	");
		free(tmp);
		i++;
	}
}


void	parsedata(int ac, char **av, t_data *data)
{
	parse(ac, av);
	doublearraylen(av, data);
	extractcubfile(data, av);
	getmap(data);
	gettextures(data);
	trimtextures(data);
	getceiling(data);
	getfloor(data);
	get_dir(data);
	get_rgb(data);
	get_rgb_v2(data);
	get_dir_v2(data);
	if (!data->dir[0] || !data->dir_2[0] || !data->rgb[0] || !data->rgb_2[0])
	{
		printf("Invalid INFOS !\n");
		ft_exit(data);
	}
	if (!check_all(data))
	{
		printf("Invalid INFOS !\n");
		ft_exit(data);
	}
	if (!validatepadding(data))
	{
		printf("Malloc Error !\n");
		ft_exit(data);
	}
	if (!validatemap(data))
	{
		printf("Invalid Map !\n");
		ft_exit(data);
	}
	if (!validateinside(data))
	{
		printf("Invalid Map !\n");
		ft_exit(data);
	}
}
