/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/27 18:37:05 by rammisse         ###   ########.fr       */
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

int gettextures(char **av, t_data *data)
{
	int     j;
	int		k;
	int		size;
	int     i;
	char    *tmp;
	int		start;
	char    *line;
	
	data->textures = malloc(sizeof(char *) * (doublearraylen(av) + 1));
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	start = 0;
	k = 0;
	size = linelen(av) + 1;
	while ((line = get_next_line(j)) != NULL)
	{
		i = 0;
		tmp = line;
		while (line[i])
		{
			if (line[i] == '.')
			{
				data->textures[k] = malloc(size);
				start = i;
				while (line[i])
					i++;
				data->textures[k] = ft_substr(line, start, i);
				k++;
			}
			i++;
		}
		free(tmp);
	}
	data->textures[k] = NULL;
	close(j);
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
}
	