/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/26 08:46:46 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void createwindow(t_mlx *mlx)
{
    mlx->win = mlx_init();
    mlx->mlxwin = mlx_new_window(mlx->win, WIDTH, LENGTH, "CUB3D");
    mlx_loop(mlx->win);
}

int parse(int ac)
{
    if (ac != 2)
        return (0);
    return (1);
}

int linelen(char **av)
{
    int j;
    size_t len;
    char *line;

    j = open(av[1], O_RDONLY);
    if (j == -1)
        return (printf("Invalid CUB File !\n"), exit(1), 1);
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
        return (printf("Invalid CUB File !\n"), exit(1), 1);
    len = 0;
    while ((line = get_next_line(j)) != NULL)
    {
        len++;
        free(line);
    }
    close(j);
    return (len);
}

int main(int ac, char **av)
{
    // t_mlx win;
    
    // (void)av;
    if (!parse(ac))
        return (printf("Invalid Input!\n"), 1);
    // createwindow(&win);
}
    