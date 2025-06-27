/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:54:54 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/26 19:28:17 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int map(t_data *data, char **av)
{
	int		j;
	int		i;
	int		size;
	char	*line;
	
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	data->map = malloc(sizeof(char *) * (doublearraylen(av) + 1));
	if (!data->map)
		return (0);
	i = 0;
	size = linelen(av) + 1;
	while ((line = get_next_line(j)) != NULL)
	{
		if (isnum(*line))
		{
			data->map[i] = malloc(size);
			ft_strlcpy(data->map[i], line, ft_strlen(line) + 1);
			i++;
		}
		free(line);
	}
	data->map[i] = NULL;
	close(j);
	return (1);
}

int getceiling(t_data *data, char **av)
{
	int		j;
	int		result;
	char	*tmp;
	char	*line;
	int		i;
	
	i = 0;
	result = 0;
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	while ((line = get_next_line(j)))
	{
		tmp = line;
		if (*line == 'C')
		{
			while (*line)
			{
				if (isnum(*line))
					result = result * 10 + (*line - '0');
				if (*line == ',' || *line == '\n')
				{
					data->ceiling[i] = result;
					result = 0;
					i++;
				}
				line++;
			}
		}
		free(tmp);
	}
	close(j);
	return (1);
}

int getfloor(t_data *data, char **av)
{
	int		j;
	int		result;
	char	*tmp;
	char	*line;
	int		i;
	
	i = 0;
	result = 0;
	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	while ((line = get_next_line(j)))
	{
		tmp = line;
		if (*line == 'F')
		{
			while (*line)
			{
				if (isnum(*line))
					result = result * 10 + (*line - '0');
				if (*line == ',' || *line == '\n')
				{
					data->ceiling[i] = result;
					result = 0;
					i++;
				}
				line++;
			}
		}
		free(tmp);
	}
	close(j);
	return (1);
}
