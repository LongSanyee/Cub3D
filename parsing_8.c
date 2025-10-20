/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 05:52:30 by rammisse          #+#    #+#             */
/*   Updated: 2025/10/20 05:53:45 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:34:49 by rammisse          #+#    #+#             */
/*   Updated: 2025/10/19 23:37:39 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	getceiling(t_data *data)
{
	int	i;

	i = 0;
	while (data->cubfile[i])
	{
		if (!ft_strncmp(data->cubfile[i], "C", 1))
			return (storecolors(data->ceiling, data->cubfile[i], data));
		i++;
	}
	return (1);
}

int	getfloor(t_data *data)
{
	int	i;

	i = 0;
	while (data->cubfile[i])
	{
		if (!ft_strncmp(data->cubfile[i], "F", 1))
			return (storecolors(data->floor, data->cubfile[i], data));
		i++;
	}
	return (1);
}
