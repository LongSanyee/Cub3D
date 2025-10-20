/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:06:10 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 19:48:34 by rammisse         ###   ########.fr       */
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
	color.color = (mlx->data.floor[0] << 16) | (mlx->data.floor[1] << 8)
		| mlx->data.floor[2];
	while (color.y < HEIGHT / 2)
	{
		color.x = 0;
		while (color.x < WIDTH)
			put_pixel(mlx, color.x++, color.y, color.color);
		color.y++;
	}
	color.y = HEIGHT / 2;
	color.color2 = (mlx->data.ceiling[0] << 16) | (mlx->data.ceiling[1] << 8)
		| mlx->data.ceiling[2];
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

void	render3dwalls(t_mlx *mlx)
{
	t_render	re;
	double		fov;

	re.i = 0;
	do_c_f(mlx);
	fov = 60 * (PI / 180);
	while (re.i < RAYS)
	{
		re.correctdistance = mlx->rays[re.i].distance
			* cos(mlx->rays[re.i].rayangle - mlx->player.rotationangle);
		re.distanceproj = (WIDTH / 2) / tan(fov / 2);
		re.wallheight = (int)((TILE / re.correctdistance) * re.distanceproj);
		re.walltop = (HEIGHT / 2) - (re.wallheight / 2);
		if (re.walltop < 0)
			re.walltop = 0;
		re.wallbottom = (HEIGHT / 2) + (re.wallheight / 2);
		if (re.wallbottom >= HEIGHT)
			re.wallbottom = HEIGHT - 1;
		re.stripwidth = WIDTH / RAYS;
		if (re.stripwidth < 1)
			re.stripwidth = 1;
		drawtexture(mlx, &re);
		re.i++;
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
