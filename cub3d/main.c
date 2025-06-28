/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/28 14:54:07 by rammisse         ###   ########.fr       */
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
		if (!ft_strncmp(data->cubfile[i], "NO ", 3) || !ft_strncmp(data->cubfile[i], "SO ", 3) ||
			!ft_strncmp(data->cubfile[i], "WE ", 3) || !ft_strncmp(data->cubfile[i], "EA ", 3))
		{
			data->textures[k] = ft_substr(data->cubfile[i], start + 3, ft_strlen(data->cubfile[i]) - 3);
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
	mlx_destroy_window(mlx->win, mlx->mlxwin);
	mlx_destroy_display(mlx->win);
	free(mlx->win);
	exit(0);
	return (0);
}

void createwindow(t_mlx *mlx)
{
	mlx->win = mlx_init();
	mlx->mlxwin = mlx_new_window(mlx->win, WIDTH, LENGTH, "CUB3D");
	mlx_hook(mlx->mlxwin, 17, 0, xbutton, mlx);
	mlx_loop(mlx->win);
}

void parsedata(int ac, char **av, t_data *data)
{
	parse(ac, av);
	doublearraylen(av, data);
	extractcubfile(data, av);
	getmap(data);
	gettextures(data);
	getceiling(data);
	getfloor(data);
}


int main(int ac, char **av)
{
	t_mlx win;

	parsedata(ac, av, &win.data);
	// createwindow(&win);
}
	