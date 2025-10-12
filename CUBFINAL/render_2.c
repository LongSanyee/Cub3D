/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:39:30 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/04 10:27:28 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cleanexit(t_mlx *mlx)
{
	freeeverything(&mlx->data);
	mlx_destroy_window(mlx->mlx, mlx->mlxwin);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int	xbutton(t_mlx *mlx)
{
	cleanexit(mlx);
	return (0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->linelength + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	dir_player(t_mlx *mlx)
{
	if (mlx->data.playerdir == 'N')
		mlx->player.rotationangle = 3 * PI / 2;
	else if (mlx->data.playerdir == 'S')
		mlx->player.rotationangle = PI / 2;
	else if (mlx->data.playerdir == 'E')
		mlx->player.rotationangle = 0;
	else if (mlx->data.playerdir == 'W')
		mlx->player.rotationangle = PI;
}

int	createmap(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (mlx->data.map[y])
	{
		x = 0;
		while (mlx->data.map[y][x])
		{
			if (isplayer(mlx->data.map[y][x]))
			{
				mlx->data.playerdir = mlx->data.map[y][x];
				mlx->player.x = x + 0.5;
				mlx->player.y = y + 0.5;
				dir_player(mlx);
				mlx->data.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (0);
}
