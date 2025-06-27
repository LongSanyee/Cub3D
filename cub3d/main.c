/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/27 20:01:05 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int parse(int ac)
{
	if (ac != 2)
		return (printf("Usage: ./cub3D FILE.CUB !\n"), exit(1), 0);
	return (1);
}

int linelen(char **av)
{
	int j;
	size_t len;
	char *line;

	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	len = 0;
	while ((line = get_next_line(j)) != NULL)
	{
		if (ft_strlen(line) > len)
			len = ft_strlen(line);
		free(line);
	}
	close(j);
	return (len);
}

int doublearraylen(char **av)
{
	int j;
	char *line;
	size_t len;
	
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	len = 0;
	while ((line = get_next_line(j)) != NULL)
	{
		len++;
		free(line);
	}
	close(j);
	return (len);
}

int	extractcubfile(t_data *data, char **av)
{
	int j;
	char *line;
	int k;

	data->cubfile = malloc((doublearraylen(av) + 1) * sizeof(char *));
	k = 0;
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	while ((line = get_next_line(j)))
	{
		data->cubfile[k] = malloc(ft_strlen(line));
		ft_strlcpy(data->cubfile[k], line, ft_strlen(line));
		k++;
	}
	data->cubfile[k] = NULL;
	close(j);
	return (1);
}

int gettextures(char **av, t_data *data, char **file)
{
	int		i;
	int		k;
	int		start;

	data->textures = malloc(sizeof(char *) * (doublearraylen(av) + 1));
	start = 0;
	k = 0;
	i = 0;
	while (file[i])
	{
		if (!ft_strncmp(file[i], "NO ", 3) || !ft_strncmp(file[i], "SO ", 3) ||
			!ft_strncmp(file[i], "WE ", 3) || !ft_strncmp(file[i], "EA ", 3))
		{
			data->textures[k] = ft_substr(file[i], start + 3, ft_strlen(file[i]) - 3);
			k++;
		}
		else
			return (-1);
		i++;
	}
	data->textures[k] = NULL;
	return (1);
}

void createwindow(t_mlx *mlx)
{
	mlx->win = mlx_init();
	mlx->mlxwin = mlx_new_window(mlx->win, WIDTH, LENGTH, "CUB3D");
	mlx_loop(mlx->win);
}

int main(int ac, char **av)
{
	// t_mlx win;
	t_data data;

	(void)ac;
	extractcubfile(&data, av);
	int i = 0;
	while (data.cubfile[i])
	{
		printf("%s", data.cubfile[i]);
		i++;
	}
}
	