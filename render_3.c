/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:40:13 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 05:48:05 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initstruct(t_player *player)
{
	player->turndirection = 0;
	player->walkdirection = 0;
	player->strafedirection = 0;
	player->rotationspeed = 4 * (PI / 180);
	player->speed = 0.06;
}

int	keypress(int key, t_mlx *mlx)
{
	if (key == ESC)
		cleanexit(mlx);
	if (key == W)
		mlx->player.walkdirection = 1;
	if (key == S)
		mlx->player.walkdirection = -1;
	if (key == A)
		mlx->player.strafedirection = -1;
	if (key == D)
		mlx->player.strafedirection = 1;
	if (key == LEFT)
		mlx->player.turndirection = -1;
	if (key == RIGHT)
		mlx->player.turndirection = 1;
	return (0);
}

int	keyrelease(int key, t_mlx *mlx)
{
	if (key == W)
		mlx->player.walkdirection = 0;
	if (key == S)
		mlx->player.walkdirection = 0;
	if (key == A)
		mlx->player.strafedirection = 0;
	if (key == D)
		mlx->player.strafedirection = 0;
	if (key == LEFT || key == RIGHT)
		mlx->player.turndirection = 0;
	return (0);
}

static int	is_within_bounds(t_mlx *data, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= (int)data->data.len
		|| map_y < 0 || map_y >= (int)data->data.k)
		return (0);
	return (1);
}

static int	is_wall(t_mlx *data, int map_x, int map_y)
{
	if (!is_within_bounds(data, map_x, map_y))
		return (1);
	return (data->data.map[map_y][map_x] == '1');
}

static int	can_move(t_mlx *data, double x, double y, int margin)
{
	int	map_x;
	int	map_y;
	int	margin_x;
	int	margin_y;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	margin_x = margin / TILE;
	margin_y = margin / TILE;
	if (is_wall(data, map_x, map_y))
		return (0);
	if (is_wall(data, map_x, map_y - margin_y))
		return (0);
	if (is_wall(data, map_x, map_y + margin_y))
		return (0);
	if (is_wall(data, map_x - margin_x, map_y))
		return (0);
	if (is_wall(data, map_x + margin_x, map_y))
		return (0);
	if (is_wall(data, map_x - margin_x, map_y - margin_y))
		return (0);
	if (is_wall(data, map_x + margin_x, map_y - margin_y))
		return (0);
	if (is_wall(data, map_x - margin_x, map_y + margin_y))
		return (0);
	if (is_wall(data, map_x + margin_x, map_y + margin_y))
		return (0);
	return (1);
}

int	update(t_mlx *mlx)
{
	double	new_x;
	double	new_y;
	double	movestep;
	double	strafe_angle;

	mlx->player.rotationangle += mlx->player.turndirection
		* mlx->player.rotationspeed;
	mlx->player.rotationangle = update_angle(mlx->player.rotationangle);
	movestep = mlx->player.walkdirection * mlx->player.speed;
	new_x = mlx->player.x + cos(mlx->player.rotationangle) * movestep;
	new_y = mlx->player.y + sin(mlx->player.rotationangle) * movestep;
	strafe_angle = mlx->player.rotationangle + (PI / 2);
	movestep = mlx->player.strafedirection * mlx->player.speed;
	new_x += cos(strafe_angle) * movestep;
	new_y += sin(strafe_angle) * movestep;
	if (can_move(mlx, new_x * TILE, new_y * TILE, 1))
	{
		mlx->player.x = new_x;
		mlx->player.y = new_y;
	}
	cast_all_rays(mlx, 0);
	render3dwalls(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlxwin, mlx->img, 0, 0);
	return (0);
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
