/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/29 20:37:42 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



void freedoublearr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void freeeverything(t_data *data)
{
	freedoublearr(data->map);
	freedoublearr(data->cubfile);
	freedoublearr(data->textures);
}

int parse(int ac, char **av)
{
	if (ac != 2)
		return (printf("Usage: ./cub3D FILE.CUB !\n"), exit(1), 0);
	if (ft_strlen(av[1]) <= 4)
		return (printf("File Extension Should be .CUB !\n"), exit(1), 0);
	else
	{
		if (!ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
			return (1);
		return (printf("File Extension Should be .CUB !\n"), exit(1), 0);
	}
}

void	doublearraylen(char **av, t_data *data)
{
	int j;
	char *line;
	size_t len;
	
	j = open(av[1], O_RDONLY);
	if (j == -1)
	{
		printf("Invalid CUB File !\n");
		exit(1);
	}
	len = 0;
	while ((line = get_next_line(j)) != NULL)
	{
		len++;
		free(line);
	}
	close(j);
	data->len = len;
}

int	extractcubfile(t_data *data, char **av)
{
	int j;
	char *line;
	int k;

	data->cubfile = malloc((data->len + 1) * sizeof(char *));
	k = 0;
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	while ((line = get_next_line(j)))
	{
		data->cubfile[k] = malloc(ft_strlen(line) + 1);
		ft_strlcpy(data->cubfile[k], line, ft_strlen(line) + 1);
		if (data->cubfile[k][ft_strlen(data->cubfile[k]) - 1] == '\n')
			data->cubfile[k][ft_strlen(data->cubfile[k]) - 1] = '\0';
		k++;
		free(line);
	}
	data->cubfile[k] = NULL;
	close(j);
	return (1);
}

int gettextures(t_data *data)
{
	int		i;
	int		k;
	int		start;

	data->textures = malloc(sizeof(char *) * (data->len + 1));
	start = 0;
	k = 0;
	i = 0;
	while (data->cubfile[i])
	{
		if (!ft_strncmp(data->cubfile[i], "NO", 2) || !ft_strncmp(data->cubfile[i], "SO", 2) ||
			!ft_strncmp(data->cubfile[i], "WE", 2) || !ft_strncmp(data->cubfile[i], "EA", 2))
		{
			data->textures[k] = ft_substr(data->cubfile[i], start + 2, ft_strlen(data->cubfile[i]) - 3);
			k++;
		}
		else
			break ;
		i++;
	}
	data->textures[k] = NULL;
	return (1);
}

int xbutton(void *param)
{
	t_mlx *mlx = (t_mlx *)param;

	freeeverything(&mlx->data);
	mlx_destroy_window(mlx->mlx, mlx->mlxwin);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
	return (0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->linelength + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_square(t_mlx *img, int map_x, int map_y, int color)
{
	size_t x, y;
	int start_x = map_x * TILE;
	int start_y = map_y * TILE;

	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			put_pixel(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void keyhelp(t_mlx *mlx, int flag)
{
	int x;
	char temp;
	int y;	

	
	y = 0;
	while (mlx->data.map[y])
	{
		x = 0;
		while (mlx->data.map[y][x])
		{
			if (isplayer(mlx->data.map[y][x]))
			{
				if (flag == 1)
				{
					if (mlx->data.map[y - 1][x] != '1')
					{
						temp = mlx->data.map[y][x];
						mlx->data.map[y][x] = mlx->data.map[y - 1][x];
						mlx->data.map[y - 1][x] = temp;
					}
				}
				else if (flag == 2)
				{
					if (mlx->data.map[y + 1][x] != '1')
					{
						temp = mlx->data.map[y][x];
						mlx->data.map[y][x] = mlx->data.map[y + 1][x];
						mlx->data.map[y + 1][x] = temp;
					}
				}
				else if (flag == 4)
				{
					if (mlx->data.map[y][x + 1] != '1')
					{
						temp = mlx->data.map[y][x];
						mlx->data.map[y][x] = mlx->data.map[y][x + 1];
						mlx->data.map[y][x + 1] = temp;
					}
				}
				else if (flag == 3)
				{
					if (mlx->data.map[y][x - 1] != '1')
					{
						temp = mlx->data.map[y][x];
						mlx->data.map[y][x] = mlx->data.map[y][x - 1];
						mlx->data.map[y][x - 1] = temp;
					}
				}
			}
			x++;
		}
		y++;
	}
}

int key_handler(int keycode, void *param)
{
	t_mlx *mlx = (t_mlx *)param;

	if (keycode == 65307)
		exit(0);
	else if (keycode == 119)
		keyhelp(mlx, 1);
	else if (keycode == 115)
		keyhelp(mlx, 2);
	else if (keycode == 97)
		keyhelp(mlx, 3);
	else if (keycode == 100)
		keyhelp(mlx, 4);
	return (0);
}

int	createwindow(t_mlx *mlx)
{
	int x;
	int y;
	y = 0;
	while (mlx->data.map[y])
	{
		x = 0;
		while (mlx->data.map[y][x])
		{
			if (mlx->data.map[y][x] == '1')
				draw_square(mlx, x, y, 0x000000);
			else if (mlx->data.map[y][x] == '0')
				draw_square(mlx, x, y, 0xFFFFFF);
			else if (isplayer(mlx->data.map[y][x]))
				draw_square(mlx, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlxwin, mlx->img, 0, 0);
	return (0);
}

void ft_exit(t_data *data)
{
	freedoublearr(data->map);
	freedoublearr(data->cubfile);
	exit(1);
}

void parsedata(int ac, char **av, t_data *data)
{
	parse(ac, av);
	doublearraylen(av, data);
	extractcubfile(data, av);
	getmap(data);
	if (!validatepadding(data))
	{
		printf("Malloc Error !\n");
		ft_exit(data);
	}
	if (!validatemap(data) || !validateinside(data))
	{
		printf("Invalid Map !\n");
		ft_exit(data);
	}
	gettextures(data);
	getceiling(data);
	getfloor(data);
}

int main(int ac, char **av)
{
	t_mlx win;

	parsedata(ac, av, &win.data);
	win.mlx = mlx_init();
	win.mlxwin = mlx_new_window(win.mlx, WIDTH, HEIGHT, "CUB3D");
	win.img = mlx_new_image(win.mlx, longestline(&win.data) * TILE, win.data.k * TILE);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.linelength, &win.endian);
	mlx_put_image_to_window(win.mlx, win.mlxwin, win.img, 0, 0);
	mlx_hook(win.mlxwin, 17, 0, xbutton, &win);
	mlx_loop_hook(win.mlx, createwindow, &win);
	mlx_key_hook(win.mlxwin, key_handler, &win);
	mlx_loop(win.mlx);
}
	