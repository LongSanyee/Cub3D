/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:40:13 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/08 14:49:10 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawcircle(int y, int x, int color, int rad, t_mlx *mlx)
{
	int	centery;
	int	centerx;
	int	dx;
	int	dy;

	centery = y - rad;
	while (centery <= y + rad)
	{
		centerx = x - rad;
		while (centerx <= x + rad)
		{
			dx = centerx - x;
			dy = centery - y;
			if ((dx * dx + dy * dy) <= (rad * rad))
				put_pixel(mlx, centerx, centery, color);
			centerx++;
		}
		centery++;
	}
}

void	drawtile(int oldy, int oldx, int color, t_mlx *mlx)
{
	int	x;
	int	y;

	y = oldy;
	while (y < oldy + TILE)
	{
		x = oldx;
		while (x < oldx + TILE)
		{
			put_pixel(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

int	drawmap(t_mlx *mlx)
{
	t_draw_R	draw;

	draw.y = 0;
	while (mlx->data.map[draw.y])
	{
		draw.x = 0;
		while (mlx->data.map[draw.y][draw.x])
		{
			draw.screenX = draw.x * TILE;
			draw.screenY = draw.y * TILE;
			if (draw.screenX < WIDTH / 2 - TILE)
			{
				if (mlx->data.map[draw.y][draw.x] == '1')
					drawtile(draw.screenY, draw.screenX, 0x0, mlx);
				else if (mlx->data.map[draw.y][draw.x] == '0')
					drawtile(draw.screenY, draw.screenX, 0xFFFFFF, mlx);
			}
			draw.x++;
		}
		draw.y++;
	}
	if ((int)((mlx->player.x * TILE)) < WIDTH / 2 - TILE)
		drawcircle((int)((mlx->player.y * TILE)),
			(int)((mlx->player.x * TILE)), 0xFF0000, 2, mlx);
	return (0);
}

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

int	update(t_mlx *mlx)
{
	double	new_x;
	double	new_y;
	double	movestep;

	mlx->player.rotationangle += mlx->player.turndirection
		* mlx->player.rotationspeed;
	mlx->player.rotationangle = update_angle(mlx->player.rotationangle);
	movestep = mlx->player.walkdirection * mlx->player.speed;
	new_x = mlx->player.x + cos(mlx->player.rotationangle) * movestep;
	new_y = mlx->player.y + sin(mlx->player.rotationangle) * movestep;
	if (!haswallat(mlx, new_x * TILE, new_y * TILE))
	{
		mlx->player.x = new_x;
		mlx->player.y = new_y;
	}
	delete_all(mlx);
	cast_all_rays(mlx, 0);
	render3dwalls(mlx);
	drawmap(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlxwin, mlx->img, 0, 0);
	return (0);
}
