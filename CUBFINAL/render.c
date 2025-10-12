/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:06:10 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/27 20:56:17 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	keyrelease(int key, t_mlx *mlx)
{
	if (key == W || key == UP)
		mlx->player.walkdirection = 0;
	if (key == S || key == DOWN)
		mlx->player.walkdirection = 0;
	if (key == A || key == LEFT)
		mlx->player.turndirection = 0;
	if (key == D || key == RIGHT)
		mlx->player.turndirection = 0;
	return (0);
}

void	init_line(t_line *l, int x0, int y0, int x1, int y1)
{
	l->x0 = x0;
	l->y0 = y0;
	l->x1 = x1;
	l->y1 = y1;
	l->dx = abs(x1 - x0);
	l->dy = -abs(y1 - y0);
	if (x0 < x1)
		l->sx = 1;
	else
		l->sx = -1;
	if (y0 < y1)
		l->sy = 1;
	else
		l->sy = -1;
	l->err = l->dx + l->dy;
}

int	step_line(t_line *l)
{
	int	e2;

	e2 = 2 * l->err;
	if (e2 >= l->dy)
	{
		l->err += l->dy;
		l->x0 += l->sx;
	}
	if (e2 <= l->dx)
	{
		l->err += l->dx;
		l->y0 += l->sy;
	}
	return (l->x0 == l->x1 && l->y0 == l->y1);
}

void	draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
	t_line	l;

	init_line(&l, x0, y0, x1, y1);
	while (1)
	{
		put_pixel(mlx, l.x0, l.y0, color);
		if (step_line(&l))
			break ;
	}
}

void	render_rays(t_mlx *mlx)
{
	int	i;
	int	startx;
	int	starty;
	int	endx;
	int	endy;

	i = 0;
	while (i < RAYS)
	{
		startx = mlx->player.x * TILE;
		starty = mlx->player.y * TILE;
		endx = mlx->rays[i].wallhitx;
		endy = mlx->rays[i].wallhity;
		if (startx < WIDTH / 2 && endx < WIDTH / 2)
			draw_line(mlx, startx, starty, endx, endy, 0xFF0000);
		i++;
	}
}
