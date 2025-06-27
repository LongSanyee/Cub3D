/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:11 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/27 17:45:24 by rammisse         ###   ########.fr       */
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


// int validatemap(char **av)
// {
    //     int     j;
    //     int     i;
    //     char    *tmp;
    //     char    *line;
    
//     j = open(av[1], O_RDONLY);
//     if (j == -1)
//         return (printf("Invalid CUB File !\n"), exit(1), 0);
//     i = 0;
//     while ((line = get_next_line(j)) != NULL)
//     {
    
//     }
// }

void createwindow(t_mlx *mlx)
{
    mlx->win = mlx_init();
    mlx->mlxwin = mlx_new_window(mlx->win, WIDTH, LENGTH, "CUB3D");
    mlx_loop(mlx->win);
}

int main(int ac, char **av)
{
    // t_mlx win;
    
    (void)av;
    parse(ac);
}
    