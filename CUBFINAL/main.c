/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/10/04 10:30:42 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	gettextures(t_data *data)
{
	int	i;
	int	k;
	int	start;

	data->textures = malloc(sizeof(char *) * (data->len + 1));
	start = 0;
	k = 0;
	i = 0;
	while (data->cubfile[i])
	{
		if (!ft_strncmp(data->cubfile[i], "NO", 2)
			|| !ft_strncmp(data->cubfile[i], "SO", 2)
			|| !ft_strncmp(data->cubfile[i], "WE", 2)
			|| !ft_strncmp(data->cubfile[i], "EA", 2))
		{
			data->textures[k] = ft_substr(data->cubfile[i], start + 2,
					ft_strlen(data->cubfile[i]) - 2);
			k++;
		}
		else
			break ;
		i++;
	}
	data->textures[k] = NULL;
	return (1);
}

void	ft_exit(t_data *data)
{
	freedoublearr(data->map);
	freedoublearr(data->cubfile);
	exit(1);
}

int	check_all(t_data *data)
{
	if (!parse_rgb(data) || !check_num(data) || !parse_dir(data))
	{
		if (!parse_rgb_v2(data) || !check_num(data) || !parse_dir_v2(data))
			return (0);
		else
			return (1);
	}
	return (1);
}

void	initdata(t_mlx *win)
{
	win->mlx = mlx_init();
	win->mlxwin = mlx_new_window(win->mlx, WIDTH, HEIGHT, "CUB3D");
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->addr = mlx_get_data_addr(win->img, &win->bpp,
			&win->linelength, &win->endian);
	load_all_textures(win);
}

int	main(int ac, char **av)
{
	t_mlx	win;

	parsedata(ac, av, &win.data);
	initdata(&win);
	createmap(&win);
	render(&win);
}
