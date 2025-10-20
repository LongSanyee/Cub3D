/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:34:34 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/21 00:53:53 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	trimtextures(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 4)
	{
		tmp = data->textures[i];
		data->textures[i] = ft_strtrim(data->textures[i], " 	");
		free(tmp);
		i++;
	}
}

void	callfuncs(int ac, char **av, t_data *data)
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
}

int	parsedata(int ac, char **av, t_data *data)
{
	callfuncs(ac, av, data);
	if (!data->dir[0] || !data->dir_2[0] || !data->rgb[0] || !data->rgb_2[0])
		return (printf("Invalid INFOS !\n"), ft_exit(data), 1);
	if (!check_all(data))
		return (printf("Invalid INFOS !\n"), ft_exit(data), 1);
	if (!validatepadding(data))
		return (printf("Malloc Error !\n"), ft_exit(data), 1);
	if (!validatemap(data))
		return (printf("Invalid Map !\n"), ft_exit(data), 1);
	if (!validateinside(data))
		return (printf("Invalid Map !\n"), ft_exit(data), 1);
	if (!check_h_w(data))
		return (printf("Invalid Map (100 * 100) !\n"), ft_exit(data), 1);
	return (0);
}
