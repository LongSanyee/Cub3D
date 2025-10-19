/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:30:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/19 19:49:57 by rammisse         ###   ########.fr       */
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

int	getresult(t_data data, t_vars vars)
{
	return (vars.result * 10 + (data.cubfile[vars.i][vars.j] - '0'));
}

int	getceiling(t_data *data)
{
	t_vars	vars;

	initvars(&vars);
	while (data->cubfile[vars.i])
	{
		if (!ft_strncmp(data->cubfile[vars.i], "C", 1))
		{
			vars.j = 1;
			while (data->cubfile[vars.i][vars.j])
			{
				if (isnum(data->cubfile[vars.i][vars.j]))
					vars.result = getresult(*data, vars);
				if (data->cubfile[vars.i][vars.j] == ','
						|| data->cubfile[vars.i][vars.j + 1] == '\0')
				{
					data->ceiling[vars.k++] = vars.result;
					vars.result = 0;
				}
				vars.j++;
			}
			break ;
		}
		vars.i++;
	}
	return (1);
}

int	getfloor(t_data *data)
{
	t_vars	vars;

	initvars(&vars);
	while (data->cubfile[vars.i])
	{
		if (!ft_strncmp(data->cubfile[vars.i], "F", 1))
		{
			vars.j = 1;
			while (data->cubfile[vars.i][vars.j])
			{
				if (isnum(data->cubfile[vars.i][vars.j]))
					vars.result = getresult(*data, vars);
				if (data->cubfile[vars.i][vars.j] == ','
						|| data->cubfile[vars.i][vars.j + 1] == '\0')
				{
					data->floor[vars.k++] = vars.result;
					vars.result = 0;
				}
				vars.j++;
			}
			break ;
		}
		vars.i++;
	}
	return (1);
}
