/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:01:35 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/14 18:18:14 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	freedoublearr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	freeeverything(t_data *data)
{
	freedoublearr(data->map);
	freedoublearr(data->cubfile);
	freedoublearr(data->textures);
}

int	parse(int ac, char **av)
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
	int		j;
	char	*line;
	char	*tmp;
	size_t	len;

	j = open(av[1], O_RDONLY);
	if (j == -1)
	{
		printf("Invalid CUB File !\n");
		exit(1);
	}
	len = 0;
	line = get_next_line(j);
	while (line)
	{
		tmp = line;
		len++;
		free(tmp);
		line = get_next_line(j);
	}
	close(j);
	data->len = len;
}

int	extractcubfile(t_data *data, char **av)
{
	int		j;
	int		k;
	char	*tmp;
	char	*line;

	data->cubfile = malloc((data->len + 1) * sizeof(char *));
	k = 0;
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	line = get_next_line(j);
	while (line != NULL)
	{
		tmp = line;
		data->cubfile[k] = malloc(ft_strlen(line) + 1);
		ft_strlcpy(data->cubfile[k], line, ft_strlen(line) + 1);
		if (data->cubfile[k][ft_strlen(data->cubfile[k]) - 1] == '\n')
			data->cubfile[k][ft_strlen(data->cubfile[k]) - 1] = '\0';
		k++;
		free(tmp);
		line = get_next_line(j);
	}
	data->cubfile[k] = NULL;
	close(j);
	return (1);
}
