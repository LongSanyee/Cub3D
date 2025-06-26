/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:54:54 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/26 09:29:11 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	filefd(char **av)
{
	int j;

	j = open(av[1], O_RDONLY);
	if (j == -1)
		return (printf("Invalid CUB File !\n"), exit(1), 0);
	return (j);
}

char **getmap(char **av)
{
	char	**map;
	int size;
	int		i;
	char	*line;
	int		j;

	j = filefd(av);
	map = malloc(sizeof(char *) * (doublearraylen(av) + 1));
	size = linelen(av) + 1;
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(j)) != NULL)
	{
		map[i] = malloc(size);
		ft_strlcpy(map[i], line, size);
		i++;
		free(line);
	}
	close(j);
	map[i] = NULL;
	return (map);
}
