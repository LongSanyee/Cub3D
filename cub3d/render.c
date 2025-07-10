/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:16:43 by rammisse          #+#    #+#             */
/*   Updated: 2025/07/08 21:23:08 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void cleanexit(t_mlx *mlx)
{
	freeeverything(&mlx->data);
	mlx_destroy_window(mlx->mlx, mlx->mlxwin);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int xbutton(t_mlx *mlx)
{
	cleanexit(mlx);
	return (0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->linelength + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

int createmap(t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (mlx->data.map[y])
	{
		x = 0;
		while (mlx->data.map[y][x])
		{
			if (isplayer(mlx->data.map[y][x]))
			{
				mlx->player.x = x + 0.5;
				mlx->player.y = y + 0.5;
				mlx->data.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (0);
}

void drawcircle(int y, int x, int color, int rad, t_mlx *mlx)
{
	int centery;
	int centerx;
	int dx;
	int dy;

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

void drawtile(int oldy, int oldx, int color, t_mlx *mlx)
{
	int x;
	int y;

	y = oldy;
	while (y < oldy + TILE)
	{
		x = oldx;
		while (x < oldx + TILE)
		{
			if (x == oldx || x == oldx + TILE - 1 || y == oldy || y == oldy + TILE - 1)
				put_pixel(mlx, x, y, 0x0);
			else
				put_pixel(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void drawdirectionline(t_mlx *mlx)
{
	int     px = (int)(mlx->player.x * TILE);
	int     py = (int)(mlx->player.y * TILE);
	double  angle = mlx->player.rotationangle;
	double  x1 = px + cos(angle) * 20;
	double  y1 = py + sin(angle) * 20;
	double  dx = x1 - px;
	double  dy = y1 - py;
	int     steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	double  x_inc = dx / steps;
	double  y_inc = dy / steps;
	double  x = px;
	double  y = py;
	int     i = 0;
	while (i < steps)
	{
		put_pixel(mlx, (int)x, (int)y, 0x00FF00);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

int drawmap(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (mlx->data.map[y])
	{
		x = 0;
		while (mlx->data.map[y][x])
		{
			if (mlx->data.map[y][x] == '1')
				drawtile(y * TILE, x * TILE, 0x0, mlx);
			else if (mlx->data.map[y][x] == '0')
				drawtile(y * TILE, x * TILE, 0xFFFFFF, mlx);
			x++;
		}
		y++;
	}
	int px = (int)((mlx->player.x * TILE));
	int py = (int)((mlx->player.y * TILE));
	drawcircle(py, px, 0xFF0000, 2, mlx);
	drawdirectionline(mlx);
	return (0);
}

int update(t_mlx *mlx)
{
	double movestep;
	double new_x;
	double new_y;

	mlx->player.rotationangle += mlx->player.turndirection * mlx->player.rotationspeed;
	movestep = mlx->player.walkdirection * mlx->player.speed;
	new_x = mlx->player.x + cos(mlx->player.rotationangle) * movestep;
	new_y = mlx->player.y + sin(mlx->player.rotationangle) * movestep;
	if (mlx->data.map[(int)new_y][(int)new_x] != '1')
	{
		mlx->player.x = new_x;
		mlx->player.y = new_y;
	}
    drawmap(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->mlxwin, mlx->img, 0, 0);
    return(0);
}

void initstruct(t_player *player)
{
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotationangle = PI / 2;
	player->rotationspeed = 0.01;
	player->rad = 3;
	player->speed = 0.004;
}

int keypress(int key, t_mlx *mlx)
{
	
	if (key == ESC)
		cleanexit(mlx);
	if (key == W || key == UP)
		mlx->player.walkdirection = 1;
	if (key == S || key == DOWN)
		mlx->player.walkdirection = -1;
	if (key == A || key == LEFT)
		mlx->player.turndirection = -1;
	if (key == D || key == RIGHT)
		mlx->player.turndirection = 1;
	return (0);
}

int keyrelease(int key, t_mlx *mlx)
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

void render(t_mlx *win)
{
	initstruct(&win->player);
	mlx_hook(win->mlxwin, 17, 0, xbutton, win);
	mlx_hook(win->mlxwin, 2, 1L << 0, keypress, win);
	mlx_hook(win->mlxwin, 3, 1L << 1, keyrelease, win);
	mlx_loop_hook(win->mlx, update, win);
	mlx_loop(win->mlx);
}
