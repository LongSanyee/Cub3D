/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:30:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 05:53:31 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	initvars(t_vars *vars)
{
	vars->i = 0;
	vars->k = 0;
	vars->result = 0;
}

int	parsevalue(char *line, int *index)
{
	int	result;

	result = 0;
	while (line[*index])
	{
		if (isnum(line[*index]))
			result = result * 10 + (line[*index] - '0');
		if (result > 255)
			return (-1);
		if (line[*index] == ',' || line[*index + 1] == '\0')
			return (result);
		(*index)++;
	}
	return (result);
}

int	storecolors(int *cf, char *line, t_data *data)
{
	int	j;
	int	k;
	int	result;

	j = 0;
	k = 0;
	while (k < 3)
	{
		result = parsevalue(line, &j);
		if (result == -1)
		{
			printf("Wrong map data !\n");
			ft_exit(data);
		}
		cf[k++] = result;
		j++;
	}
	return (1);
}
