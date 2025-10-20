/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:06:10 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 22:29:00 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_all(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	do_c_f(t_mlx *mlx)
{
	t_color	color;

	color.y = 0;
	color.color = (mlx->data.ceiling[0] << 16) | (mlx->data.ceiling[1] << 8)
		| mlx->data.ceiling[2];
	while (color.y < HEIGHT / 2)
	{
		color.x = 0;
		while (color.x < WIDTH)
			put_pixel(mlx, color.x++, color.y, color.color);
		color.y++;
	}
	color.y = HEIGHT / 2;
	color.color2 = (mlx->data.floor[0] << 16) | (mlx->data.floor[1] << 8)
		| mlx->data.floor[2];
	while (color.y < HEIGHT)
	{
		color.x = 0;
		while (color.x < WIDTH)
		{
			put_pixel(mlx, color.x, color.y, color.color2);
			color.x++;
		}
		color.y++;
	}
}

int	handlemouse(int x, int y, void *param)
{
	int			delta_x;
	t_mlx		*win;
	static int	prev_x = -1;

	(void)y;
	win = (t_mlx *)param;
	delta_x = x - prev_x;
	win->player.rotationangle += delta_x * 0.007;
	prev_x = x;
	return (0);
}

void	render(t_mlx *win)
{
	initstruct(&win->player);
	mlx_hook(win->mlxwin, 17, 0, xbutton, win);
	mlx_hook(win->mlxwin, 2, 1L << 0, keypress, win);
	mlx_hook(win->mlxwin, 3, 1L << 1, keyrelease, win);
	mlx_hook(win->mlxwin, 6, 1L << 6, handlemouse, win);
	mlx_loop_hook(win->mlx, update, win);
	mlx_loop(win->mlx);
}
