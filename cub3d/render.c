/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:16:43 by rammisse          #+#    #+#             */
/*   Updated: 2025/07/04 19:54:06 by rammisse         ###   ########.fr       */
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
	int px = (int)(mlx->player.x * TILE);
	int py = (int)(mlx->player.y * TILE);
	drawcircle(py, px, 0xFF0000, 2, mlx);
	return (0);
}

int handlekeys(t_mlx *mlx)
{
	double plrx;
	double speed;
	double plry;
	
	plrx = mlx->player.x;
	plry = mlx->player.y;
	speed = 0.03;
	mlx->player.speed = speed;
	if (mlx->player.walkdirection == 1 && mlx->data.map[(int)(plry - speed)][(int)plrx] != '1')
		mlx->player.y -= speed;
	if (mlx->player.walkdirection == -1 && mlx->data.map[(int)(plry + speed)][(int)plrx] != '1')
		mlx->player.y += speed;
	if (mlx->player.turndirection == 1 && mlx->data.map[(int)plry][(int)(plrx - speed)] != '1')
		mlx->player.x -= speed;
	if (mlx->player.turndirection == -1 && mlx->data.map[(int)plry][(int)(plrx + speed)] != '1')
		mlx->player.x += speed;
	return (0);
}


int update(t_mlx *mlx)
{
	handlekeys(mlx);
    drawmap(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->mlxwin, mlx->img, 0, 0);
    return(0);
}

void initstruct(t_player *player)
{
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotationangle = PI / 2;
	player->rotationspeed = 2 * (PI / 180);
	player->rad = 3;
	player->speed = 0.3;
}

int keypress(int key, t_mlx *mlx)
{
	if (key == W)
		mlx->player.walkdirection = 1;
	else if (key == S)
		mlx->player.walkdirection = -1;
	else if (key == A)
		mlx->player.turndirection = 1;
	else if (key == D)
		mlx->player.turndirection = -1;
	return (0);
}

int keyrelease(int key, t_mlx *mlx)
{
	if (key == W)
		mlx->player.walkdirection = 0;
	else if (key == S)
		mlx->player.walkdirection = 0;
	else if (key == A)
		mlx->player.turndirection = 0;
	else if (key == D)
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
